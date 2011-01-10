<<<<<<< local
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
        'Tsp/TspQueue.cpp',
        'Tsp/TspManager.cpp',
        'TspPy/TspPy.cpp',
    ]

    s = e.SharedLibrary( LIBPREFIX='', target = CALC_LIB_NAME,
                        source = prepare_src_files(build_dir, files_cpp))

build_shared(env, 'build/calc/')

=======
import platform

CALC_LIB_NAME = 'calc'

env = Environment()

if(platform.system() == "Linux"):
    env.Append( CPPFLAGS = '-Wall -pedantic -pthread' )
    env.Append( CPPPATH = ['/usr/include/python2.7'] )
    env.Append( LINKFLAGS = '-Wall -pthread -Wl,-soname,' + CALC_LIB_NAME )
    #env.Append( LIBPATH = ['/usr/lib/python2.7'] )
    env.Append( LIBS = [ 'boost_thread', 'boost_python', 'boost_graph' ] )
elif(platform.system() == "Windows"):
    env.Append( CPPFLAGS = ['/EHsc', '/MDd'] )
    env.Append( CPPPATH = [ Dir('C:/Program Files/boost/boost_1_44'), Dir('C:/Python27/include') ] )
    env.Append( LIBPATH = [ Dir('C:/Program Files/boost/boost_1_44/lib'), Dir('C:/Python27/libs') ] )
else:
    print 'system not supported'

def prepare_src_files( build_dir, src_files):
    src_compilation = []
    for f in src_files:
        src_compilation.append(build_dir + f)
    return src_compilation


def build_shared( env, build_dir):
    e = env.Clone()

    if(platform.system() == "windows"):
        e.Append( CPPFLAGS = ' /D "_WINDOWS" /D "_USRDLL" /D "CALC_EXPORTS" /D "_WINDLL" ' )
        e.Append( LINKFLAGS = ' /DLL ' )

    e.VariantDir( build_dir, 'calc/src/', duplicate = 0)
    files_cpp = [
        'CalcPy.cpp',
        'Tsp/Route.cpp',
        'Tsp/Tsp.cpp',
        'Tsp/TspGraph.cpp',
        'Tsp/TspQueue.cpp',
        'Tsp/TspManager.cpp',
        'TspPy/TspPy.cpp',
    ]

    s = e.SharedLibrary( LIBPREFIX='', target = CALC_LIB_NAME,
                        source = prepare_src_files(build_dir, files_cpp))

def build_tests( env, build_dir ):
    et = env.Clone()
#    et.Prepend( LIBS = [CALC_LIB_NAME] )
    if(platform.system() == "Linux"):
        et.Append( LIBS = ['python2.7', 'boost_unit_test_framework'] )
    elif(platform.system() == "Windows"):
        et.Append( LINKFLAGS = ' /SUBSYSTEM:CONSOLE ' )
    else:
        print 'system not supported'

    et.VariantDir( build_dir, 'calc/', duplicate = 0)
#   rozwiazanie chwilowe
    files_cpp = [
        'src/CalcPy.cpp',
        'src/Tsp/Route.cpp',
        'src/Tsp/Tsp.cpp',
        'src/Tsp/TspGraph.cpp',
        'src/Tsp/TspQueue.cpp',
        'src/Tsp/TspManager.cpp',
        'src/TspPy/TspPy.cpp',
        'tests/test.cpp'
    ]
    et.Program(target = 'testCpp',
               source = prepare_src_files(build_dir, files_cpp))
#    et.Program(target = 'testCpp',
#              source = prepare_src_files(build_dir, ['test.cpp']))


build_shared(env, 'build/calc/')
build_tests(env, 'build/test/')
>>>>>>> other
