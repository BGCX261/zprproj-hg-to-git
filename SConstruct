# R. Nowak, 2010-03-13   -*- mode: Python; -*-

CALC_LIB_NAME = 'calc'

env = Environment()

env.Append( CPPFLAGS = '-Wall -pedantic -pthread' )
env.Append( CPPPATH = ['/usr/include/python2.7'] )
env.Append( LINKFLAGS = '-Wall -pthread -Wl,-soname,' + CALC_LIB_NAME )
#env.Append( LIBPATH = ['/usr/lib/python2.7'] )
env.Append( LIBS = [ 'boost_thread', 'boost_python', 'boost_graph' ] )


def prepare_src_files( build_dir, src_files):
   src_compilation = []
   for f in src_files:
      src_compilation.append(build_dir + f)
   return src_compilation


def build_shared( env, build_dir):
    e = env.Clone()

    e.VariantDir( build_dir, 'calc/src/', duplicate = 0)
    files_cpp = [
        'CalcPy.cpp',
        'Tsp/Route.cpp',
        'Tsp/Tsp.cpp',
        'Tsp/TspGraph.cpp',
        'Tsp/TspManager.cpp',
        'TspPy/TspPy.cpp',
    ]

    s = e.SharedLibrary( LIBPREFIX='', target = CALC_LIB_NAME,
                        source = prepare_src_files(build_dir, files_cpp))

build_shared(env, 'build/calc/')

