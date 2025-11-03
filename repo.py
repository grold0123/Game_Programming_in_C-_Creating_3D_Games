import subprocess




args = [
    ['git','add','C:\projects\Game_Programming_in_C-_Creating_3D_Games'],#git add
    ['git','commit','-m','update'],#git commit
    ['git','push'],#git push
]

for arg in args:
    result = subprocess.run(arg)
    if result.returncode != 0:
        print("\n\nRepository not updated\n\n")
        break;
    print("\n\n")
    
print("Repository successfully updated\n\n")