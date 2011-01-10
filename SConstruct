import os, platform


CALC_LIB_NAME = 'calc'

if(platform.system() != 'Linux' and platform.system() != 'Windows'):
    print 'Unfortunately ' + platform.system() + ' is not supported'
    exit()

opts = Variables()
if(platform.system() == "Linux"):
    opts.Add(PathVariable('python_headers', 'python headers directory', '/usr/include/python2.7',PathVariable.PathIsDir))
    opts.Add(PathVariable('python_libs',    'python libraries directory', '/usr/lib/python2.7',PathVariable.PathIsDir))    
elif(platform.system() == "Windows"):
    opts.Add(PathVariable('python_headers', 'python headers directory', 'C:/Python27/include',PathVariable.PathIsDir))
    opts.Add(PathVariable('python_libs',    'python libraries directory', 'C:/Python27/libs',PathVariable.PathIsDir))        

env = Environment(variables=opts)
Help(opts.GenerateHelpText(env) )


if(platform.system() == "Linux"):
    env.Append( CPPFLAGS = '-Wall -pedantic -pthread' )
    env.Append( CPPPATH = ['${python_headers}'] )
    env.Append( LINKFLAGS = '-Wall -pthread -Wl,-soname,' + CALC_LIB_NAME )
    env.Append( LIBPATH = ['${python_libs}'] )
    env.Append( LIBS = [ 'boost_thread', 'boost_python', 'boost_graph' ] )
elif(platform.system() == "Windows"):
    env.Append( CPPFLAGS = ['/EHsc', '/MDd'] )
    env.Append( CPPPATH = [ Dir('C:/Program Files/boost/boost_1_44'), Dir('${python_headers}') ] )
    env.Append( LIBPATH = [ Dir('C:/Program Files/boost/boost_1_44/lib'), Dir('${python_libs}') ] )
    env.Append( CPPFLAGS = ' /D "_WINDOWS" /D "_USRDLL" /D "CALC_EXPORTS" /D "_WINDLL" ' )
    env.Append( LINKFLAGS = ' /DLL ' )    



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

def build_tests( env, build_dir ):
    et = env.Clone()
#    et.Prepend( LIBS = [CALC_LIB_NAME] )
    if(platform.system() == "Linux"):
        et.Append( LIBS = ['python2.7', 'boost_unit_test_framework'] )
    elif(platform.system() == "Windows"):
        et.Append( LINKFLAGS = ' /SUBSYSTEM:CONSOLE ' )

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
