import os

# Define the path to your text file
input_file_path = 'xss-payload-list.txt'
with open(input_file_path, 'r') as file:
    lines = file.readlines()

# Iterate over each line and create a new folder with that name
for line in lines:
    # Strip any leading/trailing whitespace characters (like newlines)
    folder_name = line.strip()
    if folder_name:  # Check if the line is not empty
        try:
            # Create a new directory with the name from the line
            os.makedirs(folder_name, exist_ok=True)
            print(f"Folder '{folder_name}' created successfully.")
        except Exception as e:
            print(f"An error occurred while creating the folder '{folder_name}': {e}")
