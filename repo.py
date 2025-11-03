import subprocess




args = [
    ['git','add','C:\projects\Game_Programming_in_C-_Creating_3D_Games'],#git add
    ['git','commit','-m','update'],#git commit
    ['git','push'],#git push
]

for arg in args:
    subprocess.run(arg)
    print("\n\n")
    
print("Repository successfully updated\n\n")