#%%
import time
import pandas as pd
import subprocess
import shutil
import os

# Get the current time
start_time = time.time()

workdir=os.getcwd() # gives current working directory
micromegas_path = "/home/pmfig/dev/micromegas_5.3.41/IDM" 


parameter_file = "input-mO.dat"
template_file = "data-template.par"
output_file = "file.par"

shutil.copy("../data/micrOMEGAs/input-mO.dat", os.path.join(micromegas_path, "input-mO.dat")) # copy the content of the source file to the destination file or directory. shutil.copy(source, destination, *, follow_symlinks = True)

# print(os.path.join(micromegas_path, "input-mO.dat"))

os.chdir(micromegas_path) # A complete path of directory to be changed to new directory path. method in Python used to change the current working directory to specified path. It takes only a single argument as new directory path.

print("Parameter file: " + "../data/micrOMEGAs/input-mO.dat")
print("Template file: " + micromegas_path + "/" + template_file)
print("Transition file: " + output_file)

# %%
# This opens the parameter file as a table
parameters = pd.read_csv(parameter_file, header=None, delim_whitespace=True)
parameters.columns = ["BP", "C2", "C3", "C4", "C5", "C6", "C7"]
parameters["Omega"]=0.0

# %%
# Iterate through the points
print("Calculating Relic Density...")
index = 0
for idx, row in parameters.iterrows():
    # Open the micro-omegas template file
    with open(template_file, "rt") as fin:
        # Replace the occurrences
        with open(output_file, "wt") as fout:
            new_file = fin.read()
            new_file = new_file.replace("C2", str(row["C2"]))
            new_file = new_file.replace("C3", str(row["C3"]))
            new_file = new_file.replace("C4", str(row["C4"]))
            # new_file = new_file.replace("C5", str(row["C5"] / 2))
            # new_file = new_file.replace("C6", str(row["C6"] / 2))
            new_file = new_file.replace("C5", str(row["C5"]))
            new_file = new_file.replace("C6", str(row["C6"]))
            new_file = new_file.replace("C7", str(row["C7"] / 2))
            fout.write(new_file)
    # Call a shell subprocess to run microOmegas. Saves the result to res_idx.dat, where idx is the index of the parameter row in the original file
    output= subprocess.run(
        f"./main file.par".split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )
    omega=output.stdout.decode("utf-8").split("Omega=")[1].split("\n")[0]
    if float(omega) >= 0.1175 and float(omega) <= 0.1219: 
        print("Got one at %d" %idx)
    elif float(omega) > 0.1219:
        print("Point above at %d" %idx)
    parameters.loc[idx,"Omega"]=float(omega)

print("Writting output file: output-mO.dat")
headers = ["BP", "mh", "MH", "MA", "MC", "la2", "laL", "Omega"]
parameters.to_csv("output-mO.dat",sep=" ",header=headers, index=False, float_format="%.11E")

shutil.move("output-mO.dat", os.path.join(workdir, "../data/micrOMEGAs/output-mO.dat"))

os.remove("input-mO.dat")

os.chdir(workdir)

print("Output file: " + "../data/micrOMEGAs/output-mO.dat")

# Get the current time again
end_time = time.time()
# Calculate the running time
running_time = end_time - start_time
# Print the running time
if running_time >= 60:
    print("Running time: %.3f minutes" % (running_time/60))
else:
    print("Running time: %.3f seconds" % running_time)
