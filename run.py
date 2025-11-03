import subprocess,pathlib,os,time,sys

base_dir = pathlib.Path(r'C:\projects\Game_Programming_in_C-_Creating_3D_Games')

source_dir = base_dir/'source'
build_dir = base_dir/'build'


if len(sys.argv) == 0:
    print("No project name provided")
else:
    project_name = sys.argv[1]
    project_dir = source_dir/project_name
    source = [
        str(cpp)
        for cpp in project_dir.glob("*.cpp")        
    ]
    build = str(build_dir/project_name)
    include_dir = base_dir/'include'
    lib_dir = base_dir/'lib'    
    args = [
        'g++',*source,
        '-o',build,
        f'-I{include_dir}',
        f'-L{lib_dir}',    
        '-lSDL3',
        '-lSDL3_image'
        ]


    os.system("cls")
    print("\n\n========================Building program========================\n")
    result = subprocess.run(args)
    if result.returncode == 0:
        print("\n\n========================Build successful========================\n\n")
        print("========================Opening Program========================\n\n")
        time.sleep(.5)
        os.system('cls')
        subprocess.run([build])
    else:
        print("\n\n========================Build not successful========================\n\n")
        print(result.stdout)
        print(result.stderr)
        print("\n\n")
