import pathlib,subprocess ,sys

base_dir = r'C:\projects\Game_Programming_in_C-_Creating_3D_Games'
#get argv as source dir name
if len(sys.argv) > 1:
    project_name = sys.argv[1]        
#make a project dir
    project_dir = pathlib.Path(base_dir+"/source/"+project_name)
    project_dir.mkdir(exist_ok=True)
#create main in project dir
    main_cpp = project_dir/'main.cpp'
    main_cpp.touch(exist_ok=True)
#write template for main cpp
    with open(main_cpp,'w') as file:
        file.write("/*************************************\n")
        file.write(f'{project_name}\n')
        file.write("**************************************/\n")
        file.write('#include<iostream>\n')
        file.write('#include<SDL3/SDL.h>\n')
        file.write('int main(){\n\treturn 0;\n}\n')

