import os, sys, platform, re
import distutils.sysconfig
import SCons.Builder

CALC_LIB_NAME = 'calc'
CALC_LIB_FILE_NAME = CALC_LIB_NAME + distutils.sysconfig.get_config_var('SO')   



mxmlBuilder = SCons.Builder.Builder( action = 'mxmlc $SOURCE -output $TARGET' )

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
    
opts.Add(BoolVariable('run','Set to 1 to start django server with tsp application',0) )
opts.Add(BoolVariable('tests','Set to 1 if you want to perform tests',0) )
opts.Add(BoolVariable('sync','Set to 1 to synchronize database',0) )     

run = ARGUMENTS.get('run',0)
tests = ARGUMENTS.get('tests',0)
sync = ARGUMENTS.get('sync',0)   

#create environment
if(platform.system() == "Linux"):
    env = Environment(variables=opts)
else:
    #force 32bit build on windows
    env = Environment(variables=opts, TARGET_ARCH='x86')

#python name eg. python2.6, python2.7
python_name = os.path.basename(str(env.Dir('$python_libs'))) 


Help(opts.GenerateHelpText(env) )

env.Append( ENV = {'PATH' : os.environ['PATH'] })
env.Append( BUILDERS = {'BuildMXML': mxmlBuilder} )
env.Append( LIBPATH = [ Dir('./') ] )

#set flags etc
if(platform.system() == "Linux"):
    os.putenv('PYTHONPATH', os.getcwd() )
    env.Append( CPPFLAGS = '-Wall -pedantic -pthread' )
    env.Append( CPPPATH = [env.Dir('${python_headers}')] )
    env.Append( LIBPATH = [env.Dir('${python_libs}')] )
    env.Append( LIBS = [ 'boost_thread', 'boost_python', 'boost_graph' ] )        
    env.Append( LINKFLAGS = '-Wall -pthread')

elif(platform.system() == "Windows"):
    os.putenv('PYTHONPATH', os.getcwd() )
    env.Append( CPPFLAGS = ['/EHsc'] )
    env.Append( CPPPATH = [ env.Dir('$boost_path'), env.Dir('$python_headers') ] )
    env.Append( LIBPATH = [ env.Dir('$boost_libs'), env.Dir('$python_libs') ] )
    env.Append( CPPDEFINES=['_CONSOLE'])    

def create_sources_paths(build_dir, src_files):
    return [build_dir + f for f in src_files]



def build_calc( env, build_dir):
    e = env.Clone()

    e['SHLIBPREFIX']='' #get rid of lib prefix
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


#buduje klienta (Adobe flex)
def build_client( env, build_dir ):
   env.Install(build_dir, 'client/wrapper/client.html')
   env.Install(build_dir,'client/wrapper/swfobject.js')
   swf_client = env.BuildMXML( target = build_dir + 'client.swf', source = 'client/src/client.mxml' )
   env.Depends( swf_client,
                [ 'client/src/client.mxml',
                  'client/src/config/Config.as',
                  'client/src/dialogs/AddCityDialog.mxml',
                  'client/src/dialogs/AddRouteDialog.mxml',
                  'client/src/dialogs/ProgressDialog.mxml', ] )
   return



if tests == '1':
    #tworzy link do biblioteki bez numeru wersji
    if(platform.system() == "Linux"):
        link_file = 'server/'+CALC_LIB_FILE_NAME
        os.link(CALC_LIB_FILE_NAME, link_file)    
        os.system('./calc-test')
        os.system(python_name +' server/config/manage.py test')
        os.remove(link_file)
    else:
        os.system('calc-test');
        os.system('python server/config/manage.py test')
        
elif run == '1':
    if(platform.system() == "Linux"):
        link_file = 'server/'+CALC_LIB_FILE_NAME 
        os.link(CALC_LIB_FILE_NAME, link_file)
        os.system('firefox http://127.0.0.1:8000/traveler/client/client.html&')
        os.system(python_name +' server/config/manage.py runserver')
        os.remove(link_file)        
    else:
        lib = shutil.copy(CALC_LIB_FILE_NAME + '.dll', CALC_LIB_NAME + '.pyd')
        os.system('start python server\\config\\manage.py runserver')
        os.system('\"c:\\Program Files\\Mozilla Firefox\\firefox.exe\" http://127.0.0.1:8000/traveler/client/client.html')
        
elif sync == '1':
    if(platform.system() == "Linux"):
        os.system(python_name +'  server/config/manage.py syncdb --noinput')
    else:
        os.system('python server\\config\\manage.py syncdb --noinput')
        
else:
    build_calc(env, 'build/calc/')
    build_calc_tests(env, 'build/tests/')
    build_client(env, 'build/client/')

