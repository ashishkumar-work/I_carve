# I_carve (more user friendly and stable version will be released soon)

![I_carve](https://github.com/ashishkumar-work/I_carve/blob/main/i_carve.png)


  <h3><strong>I_carve</strong> is a tool for carving and recovery of parmenently deleted files</h3>
----------------------------------------------------------------------------------------------------------------

<h2>Usage</h2>
<h4>~ Make a disk image of the storage you want to carve, tools like FTK imager, dc3dd or any disk image creator can be used for this step</h4>
<h4>~Download the carver.c and def.h and compile it with gcc</h4>
<h4>~run it with, <code>{your_comipiled_binary}.exe  {name of the disk image} {destination_of_images_carved_and_reconstructed} {file_type}</code></h4>

------------------------------------------------------------------------------------------------------------------
<h3>File types supported in current version</h3>
~ PNG
~ JPG/JPEG

-----------------------------------------------------------------------------------------------------------------

<h3>What is file carving</h3>
<h5>File carving is a process used in computer forensics to extract data from a disk drive or other storage device without the assistance of the file system that originality created the file. It is a method that recovers files at unallocated space without any file information and is used to recover data and execute a digital forensic investigation. It also called "carving," which is a general term for extracting structured data out of raw data, based on format specific characteristics present in the structured data.


As a forensics technique that recovers files based merely on file structure and content and without any matching file system meta-data, file carving is most often used to recover files from the unallocated space in a drive. Unallocated space refers to the area of the drive which no longer holds any file information as indicated by the file system structures like the file table. In the case of damaged or missing file system structures, this may involve the whole drive. In simple words, many filesystems do not zero-out the data when they delete it. Instead, they simply remove the knowledge of where it is. File carving is the process of reconstructing files by scanning the raw bytes of the disk and reassembling them. This is usually done by examining the header (the first few bytes) and footer (the last few bytes) of a file.</h5>
source: https://resources.infosecinstitute.com/topics/digital-forensics/file-carving/
