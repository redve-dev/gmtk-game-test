project('my_project', 'cpp',
  default_options: ['warning_level=3', 'cpp_std=c++20'])

EXECUTABLE_NAME='exec'

src_arr = [
  'main.cpp',
  'func.cpp',
  'Tile/Tile.cpp',
  'Player/Player.cpp',
  'AudioPlayer/AudioPlayer.cpp',
]

deps_arr = [
  'sdl2',
  'sdl2_image',
  'sdl2_mixer'
  ]

src = []
foreach file : src_arr
  src += 'src/' + file
endforeach

deps = []
foreach dep : deps_arr
  deps += dependency(dep)
endforeach

executable(EXECUTABLE_NAME, sources: src, dependencies: deps)
