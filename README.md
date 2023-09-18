# LinuxCppEmbarque AIQWA
Exploitation d'une API en CPP sur Linux embarqué

## L'echelle du graphique s'adapte automatiquement au nombre d'échantilleons et à l'amplitude des datas
## Sources C++ dans /devel/AIrQualityWAtch
## exemples de datas json dans /datas
## exemples de graphiques dans /charts
## AIQWA.config permet de modifier certains parametres sans avoir à recompiler (dans /root pour le moment, mais a vocation à être installé dans /usr/share/...
## /devel/AIrQualityWAtch contient un script crossCompil qui copie l'executable généré dans overlay/root/bin/airQualityWatch-qemu
##  airQualityWatch-qemu est appelé par cron toutes les 5 * * * * 
###  Les datas récupérées sur l'API sont stockées dans /home/sylvain/datas
### Les graphiques générés sont enregistrés deas /home/sylvain/charts
### Un fichier json AirQualityWatch.json dans /home/sylvain/datas est incrémenté à chaque download et contient toutes les données.

## Ebauche de rapport dans Procedure.pdf

