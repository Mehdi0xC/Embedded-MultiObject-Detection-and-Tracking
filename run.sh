ssh pi@192.168.1.7 "cd ~/Desktop/vision; rm -f -r *"
scp -r  ~/Desktop/temp/vision pi@192.168.1.7:~/Desktop/

ssh pi@192.168.1.7 "cd ~/Desktop/vision; bash remote_run.sh"
