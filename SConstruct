import os, sys, platform
import distutils.sysconfig

CALC_LIB_NAME = 'calc'



python_version = platform.python_version_tuple()

#check if we support this platform
if(platform.system() != 'Linux' and platform.system() != 'Windows'):
    print 'Unfortunately ' + platform.system() + ' is not supported'
    exit()

#set variables
opts = Variables('custom.py')
if(platform.system() == "Linux"):
    opts.Add(PathVariable('python_headers', 'python headers directory', distutils.sysconfig.get_python_inc(), PathVariable.PathIsDir))
    opts.Add(PathVariable('python_libs',    'python libraries directory', distutils.sysconfig.get_python_lib(standard_lib = True), PathVariable.PathIsDir))    
elif(platform.system() == "Windows"):
    opts.Add(PathVariable('python_headers', 'python headers directory', 'C:/Python26/include',PathVariable.PathIsDir))
    opts.Add(PathVariable('python_libs',    'python libraries directory', 'C:/Python26/libs',PathVariable.PathIsDir))        
    
    opts.Add(PathVariable('boost_path',     'boost directory', 'C:/Program Files (x86)/boost/boost_1_44',PathVariable.PathIsDir))
    opts.Add(PathVariable('boost_libs',     'boost libs directory', '$boost_path'+'/lib',PathVariable.PathIsDir))     

#create environment
if(platform.system() == "Linux"):
    env = Environment(variables=opts)
else:
    #force 32bit build on windows
    env = Environment(variables=opts, TARGET_ARCH='x86')


Help(opts.GenerateHelpText(env) )


#set flags etc
if(platform.system() == "Linux"):
    env.Append( CPPFLAGS = '-Wall -pedantic -pthread' )
    env.Append( CPPPATH = [env.Dir('${python_headers}')] )
    env.Append( LIBPATH = [env.Dir('${python_libs}')] )
    env.Append( LIBS = [ 'boost_thread', 'boost_python', 'boost_graph' ] )        
    env.Append( LINKFLAGS = '-Wall -pthread')
elif(platform.system() == "Windows"):
    os.putenv('PATH', os.getcwd() + ';' + os.getenv('PATH') )
    env.Append( CPPFLAGS = ['/EHsc'] )
    env.Append( CPPPATH = [ env.Dir('$boost_path'), env.Dir('$python_headers') ] )
    env.Append( LIBPATH = [ env.Dir('$boost_libs'), env.Dir('$python_libs') ] )
    env.Append( CPPDEFINES=['_CONSOLE'])    

def create_sources_paths(build_dir, src_files):
    return [build_dir + f for f in src_files]


def build_calc( env, build_dir):
    e = env.Clone()

    e['SHLIBPREFIX']=''
    e['SHLIBSUFFIX']=distutils.sysconfig.get_config_var('SO')       
    
    calc_sources = [
        'CalcPy.cpp',
        'Tsp/Route.cpp',
        'Tsp/Tsp.cpp',
        'Tsp/TspGraph.cpp',
        'Tsp/TspQueue.cpp',
        'Tsp/TspManager.cpp',
        'TspPy/TspPy.cpp',
    ]   
    
    pld = str(e.Dir('$python_libs'))
    if(platform.system() == "Linux"):
        e.Append( LIBS = [os.path.basename(pld)] ) 
        e.Append( LINKFLAGS = '-Wl,-soname,' + CALC_LIB_NAME )
        
    else:
        e.Append( CPPFLAGS = ['/MDd'] )   
        #force static boost python linkage, this is the only way to get it working
        e.Append( CPPDEFINES=['BOOST_PYTHON_STATIC_LIB', 'BOOST_PYTHON_DYNAMIC_MODULE'])

    e.VariantDir( build_dir, 'calc/src/', duplicate = 0)

    s = e.SharedLibrary(target=CALC_LIB_NAME, source=create_sources_paths(build_dir, calc_sources))						

def build_calc_tests( env, calc_tests_build_dir ):
    et = env.Clone()
    pld = str(et.Dir('$python_libs'))    
    if(platform.system() == "Linux"):
        et.Append( LIBS = [os.path.basename(pld), 'boost_unit_test_framework'] )
    else:
        et.Append( LINKFLAGS = ' /SUBSYSTEM:CONSOLE ' )
        
    calc_tests_sources = [
        'src/Tsp/Route.cpp',
        'src/Tsp/Tsp.cpp',
        'src/Tsp/TspGraph.cpp',
        'src/Tsp/TspQueue.cpp',
        'src/Tsp/TspManager.cpp',
        'tests/test.cpp'
    ]   
    
    et.VariantDir( calc_tests_build_dir, 'calc/', duplicate = 0)    
    
    sources =  create_sources_paths(calc_tests_build_dir, calc_tests_sources)
    et.Program(target = CALC_LIB_NAME + '-test', source = sources)


build_calc(env, 'build_calc/')
build_calc_tests(env, 'build_tests/')
