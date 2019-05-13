from building import *
import rtconfig

# get current directory
cwd     = GetCurrentDir()
# The set of source files associated with this SConscript file.
src     = Glob('inc/*.h')
src     = Glob('src/*.c')
src     = Glob('src/*.cpp')

if GetDepend('AD7746_USING_READ_TEMPERATURE'):
	src    += Glob('examples/ad7746_read_temperature.cpp')

if GetDepend('AD7746_USING_READ_WRITE'):
	src    += Glob('examples/ad7746_read_write.cpp')

if GetDepend('AD7746_USING_READ_CAPACITANCE'):
	src    += Glob('examples/ad7746_read_capacitance.cpp')

if GetDepend('AD7746_USING_READ_CAPACITANCE_EXTENSION'):
	src    += Glob('examples/ad7746_read_capacitance_extension.cpp')

path    = [cwd + '/']
path   += [cwd + '/src']

LOCAL_CCFLAGS = ''

group = DefineGroup('AD7746', src, depend = ['PKG_USING_AD7746'], CPPPATH = path, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')
