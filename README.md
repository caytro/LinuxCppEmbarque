# LinuxCppEmbarque AIQWA
Exploitation d'une API en CPP sur Linux embarqué

## Sources C++ dans devel/AIrQualityWAtch
### devel/AIrQualityWAtch contient un script crossCompil qui copie l'executable généré dans overlay/root/bin/airQualityWatch-qemu
###  Cet executable est appelé par cron toutes les 5 * * * * 
###  les datas récupérées sur l'API sont stockées (provisoire) dans /tmp/AirQualityWatch-2023-09-15T12:00:00.000Z.json
### A terme, un seul fichier json contiendra les 72 derniers enregistrements (3 jours)

## Ebauche de rapport dans Procedure.pdf

