#!/usr/bin/env python2.7

# Script for generating projects from source code templates

#------------------------------------------------------------------------------
# Imports
#------------------------------------------------------------------------------

import sys

try:
    import argparse
except ImportError as err:
    if sys.hexversion < 0x02070000:
        print >>sys.stderr, 'Error: this script requires Python 2.7 or above'
    raise err

import os
import re
import shutil

#------------------------------------------------------------------------------
# Global constants
#------------------------------------------------------------------------------

LINE_WIDTH = 80
TEMPLATE_ROOT = os.path.join(sys.path[0], '..', 'templates')

# Pattern for variables whose values' case is left unchanged
VAR_PATTERN_NC = r'{{KEY}}'

# Pattern for variables whose values are made lower case when substituting
VAR_PATTERN_LC = r'{{KEY}l}'

# Pattern for variables whose values are made upper case when substituting
VAR_PATTERN_UC = r'{{KEY}u}'

# Pattern used to search for all variables, regardless of case
VAR_PATTERN_ANY = r'{{KEY}}'

#------------------------------------------------------------------------------
# Classes
#------------------------------------------------------------------------------

class ArgumentParser(argparse.ArgumentParser):
    class SubstAction(argparse.Action):
        def __call__(self, parser, namespace, values, option_string=None):
            match = re.match(r'^(\w+)=(\w*)$', str(values))
            if match:
                (key, value) = match.groups()
                if key in namespace.subst:
                    print_warning("key '{0:s}' is provided more than once".
                                  format(key))
                if 'PROJECT' == key:
                    print_warning("key 'PROJECT' is a reserved word")
                else:
                    namespace.subst[key] = value
            else:
                usage_error("'invalid key-value pair '{0:s}'".
                            format(str(values)))

    def __init__(self):
        description = 'Code generation script'

        epilog = 'Available project types:\n  ' + \
                 '\n  '.join(sorted(TemplateDict().keys()))
        epilog += '\n\nVariable substitutions (project types in parentheses):\n'
        subs = substitution_dict()
        for var in sorted(subs.keys()):
            epilog += '  {0:s} ({1:s})\n'.format(var, ', '.join(subs[var]))

        version = '0.1'

        argparse.ArgumentParser.__init__(self, description = description,
                                        formatter_class=
                                            argparse.RawDescriptionHelpFormatter,
                                        epilog = epilog)

        # Positional arguments
        self.add_argument('project_type',
                          metavar='TYPE',
                          help='Type of project')
        self.add_argument('project_name',
                          metavar='NAME',
                          help='Name of project')

        # Options
        self.add_argument('-o', '--output',
                          dest='output_dir',
                          help='output directory (defaults to ./NAME)')
        self.add_argument('-n', '--dry-run',
                          dest='dry_run', default=False,
                          action='store_true',
                          help='just show what would be done')
        self.add_argument('-f', '--force',
                          dest='force', default=False,
                          action='store_true',
                          help="don't prompt for confirmation")
        self.add_argument('-s', '--subst',
                          dest='subst', default={},
                          action=ArgumentParser.SubstAction,
                          metavar='KEY=VALUE',
                          help='key-value pair for substitution')
        self.add_argument('-v', '--verbose',
                          dest='verbose', default=False,
                          action='store_true',
                          help='produce verbose output')
        self.add_argument('-V', '--version',
                          dest='version',
                          action='version',
                          version=version,
                          help="show program's version number and exit")

class Template(object):
    '''
    Class representing template for a given project type
    '''
    def __init__(self, name):
        self.__name = name
        self.__files = []
        self.__vars = []
        self.root = os.path.join(TEMPLATE_ROOT, self.__name)

    def __list_files(self):
        for root, folders, files in os.walk(self.root):
            for file in files:
                self.__files.append(os.path.relpath(
                                    os.path.join(root, file), self.root))

    def __list_vars(self):
        vars = set()
        for file in self.files:
            fh = open(os.path.join(self.root, file))
            pat = re.compile(pattern_any(r'\w+'))
            for line in fh:
                for match in [m[2:-2] for m in pat.findall(line)]:
                    vars.add(match)
        self.__vars = list(vars)

    @property
    def files(self):
        '''
        Lazily construct and return list of files in this project
        '''
        if not len(self.__files):
            self.__list_files()
        return self.__files

    @property
    def vars(self):
        '''
        Lazily construct and return list of variable substitutions
        for this project
        '''
        if not len(self.__vars):
            self.__list_vars()
        return self.__vars

class TemplateDict(object):
    '''
    Singleton containing the dictionary of available templates
    '''
    __instance = None
    class __impl:
        def __init__(self):
            self.templates = dict([(name, Template(name))
                                    for name in os.listdir(
                                                   os.path.join(
                                                       sys.path[0],
                                                       '..', 'templates'))])
    def __init__(self):
        if not TemplateDict.__instance:
            TemplateDict.__instance = TemplateDict.__impl()
        self.__dict__['_TemplateDict__instance'] = TemplateDict.__instance

    def __getattr__(self, name):
        return getattr(TemplateDict.__instance.templates, name)

    def __getitem__(self, index):
        return TemplateDict.__instance.templates[index]

#------------------------------------------------------------------------------
# Utility functions
#------------------------------------------------------------------------------

def pattern_normal(key):
    return VAR_PATTERN_NC.replace('KEY', key)

def pattern_lower(key):
    return VAR_PATTERN_LC.replace('KEY', key)

def pattern_upper(key):
    return VAR_PATTERN_UC.replace('KEY', key)

def pattern_any(key):
    return VAR_PATTERN_ANY.replace('KEY', key)

def substitution_dict():
    d = dict()
    for key in TemplateDict().keys():
        for var in TemplateDict()[key].vars:
            if 'PROJECT' != var:
                if var in d:
                    d[var].append(key)
                else:
                    d[var] = [key]
    return d

def usage_error(message):
    print_error(message)
    ArgumentParser().print_help()
    exit(1)

def print_warning(message):
    print >> sys.stderr, 'Warning:', message

def print_error(message):
    print >> sys.stderr, 'Error:', message

def parse_command_line():
    '''
    Return: argparse.Namespace
    '''
    parser = ArgumentParser()
    args = parser.parse_args()
    if not args.output_dir:
        args.output_dir = args.project_name.lower()
    return args

def print_summary(args):
    data=[['project_type', 'Project type'],
         ['project_name',  'Project name'],
         ['output_dir',    'Output directory'],
         ['dry_run',       'Dry run']]

    keys = [x[1] for x in data]
    values = [getattr(args, x[0]) for x in data]

    maxkeylen = max([len(k) for k in keys + args.subst.keys()])
    maxvaluelen = max([len(str(v)) for v in values +
                                            args.subst.values()])
    rightcolpos = LINE_WIDTH - maxvaluelen - 2

    print '-' * LINE_WIDTH
    print 'Summary of options'
    print '-' * LINE_WIDTH

    def print_line(key, value):
        print ' '+ key, ('.' * (rightcolpos - len(key) - 2)), value

    for (index, key) in enumerate(keys):
        print_line(key, values[index])

    if len(args.subst):
        print '\nSubstitutions:\n'
        for key in sorted(args.subst.keys()):
            print_line(key, args.subst[key])

    print '-' * LINE_WIDTH

def process_file(args, source, dest):
    print "Creating file " + dest
    source_file = open(source)
    dest_file = open(dest, 'w')
    for line in source_file:
        for key in args.subst.keys():
            value = args.subst[key]
            line = line.replace(pattern_normal(key), value)
            line = line.replace(pattern_lower(key), value.lower())
            line = line.replace(pattern_upper(key), value.upper())
        print >>dest_file, line,

def main(args):
    args.subst['PROJECT'] = args.project_name
    template = TemplateDict()[args.project_type]

    missing_vars = set(template.vars) - set(args.subst.keys())
    if missing_vars:
        usage_error('missing variables: ' + str(list(missing_vars)))

    extra_vars = set(args.subst.keys()) - set(template.vars)
    if extra_vars:
        print_warning('extra variables will be ignored: ' +
                      str(list(extra_vars)))

    if '.' != args.output_dir:
        if os.path.exists(args.output_dir):
            if not args.force:
                ans = raw_input("Path '" + args.output_dir + "' exists: delete? [y|n] ")
                if ans != 'y':
                    exit(0)
            if os.path.isdir(args.output_dir):
                print 'Removing directory ' + args.output_dir
                shutil.rmtree(args.output_dir)
            else:
                print 'Removing file ' + args.output_dir
                os.remove(args.output_dir)
        print 'Creating directory ' + args.output_dir
        os.mkdir(args.output_dir)

    for dir in set([os.path.dirname(f) for f in template.files
                                       if os.path.dirname(f)]):
        subdir = os.path.join(args.output_dir, dir)
        print 'Creating directory ' + subdir
        os.mkdir(subdir)

    for file in template.files:
        source = os.path.join(template.root, file)
        file = file.replace('__PROJECT__', args.project_name.lower())
        dest = os.path.join(args.output_dir, file)
        process_file(args, source, dest)

#------------------------------------------------------------------------------
# Main
#------------------------------------------------------------------------------

args = parse_command_line()

# Check TYPE argument
if not args.project_type in TemplateDict().keys():
    usage_error("project type '{0:s}' is invalid".format(args.project_type))

if args.verbose:
    print_summary(args)

main(args)

