import os

#This is a structurally recursive function which traverses a
#hierarchy of folders. This allows one to run a subroutine
#based on whether or not a file is found or a folder is found

def rest(lst):
    return lst[1:len(lst)]

def first(lst):
    return lst[0]

def parse_indexes(directory_content, path, recurse = -1):
    if recurse == 0:
        return True
    else:
        if len(directory_content) == 0:
            return True
        elif os.path.isdir(path+first(directory_content)) == False:
            #run subroutine for a file
            #print(path+first(directory_content))
            return True and parse_indexes(rest(directory_content), path, recurse)
        else:
            #run subroutine for a folder
            folder_contents = os.listdir(path+first(directory_content))
            #print(path+first(directory_content))
            return True and parse_indexes(folder_contents, str(path+first(directory_content)+'/'), (recurse - 1)) and parse_indexes(rest(directory_content), path, recurse)
                    
#print(parse_indexes(os.listdir(os.getcwd()),'',2)) 
