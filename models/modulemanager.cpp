#include "modulemanager.h"

namespace Model {
    ModuleManager::ModuleManager()
    {
        listModule.append(new Module(Modules::Accceuil,"Acceuil"));
        listModule.append(new Module(Modules::Medecin,"Medecin"));
        listModule.append(new Module(Modules::Hospitalisation,"Hospitalisation"));
        listModule.append(new Module(Modules::BlocOperatoire,"Bloc opératoire"));
        listModule.append(new Module(Modules::Ophtalmologie,"Ophtalmologie"));
        listModule.append(new Module(Modules::Pharmacie,"Pharmacie"));
        listModule.append(new Module(Modules::Encaissement,"Encaissement"));
        listModule.append(new Module(Modules::Personnel,"Personnel"));
        listModule.append(new Module(Modules::Comptabilite,"Comptabilité"));
        listModule.append(new Module(Modules::Statistiques,"Statistiques"));
        listModule.append(new Module(Modules::Parametrage,"Paramétrage"));
        listModule.append(new Module(Modules::Securite,"Securité"));

        listDetailModule.append(new DetailsModule(AcceuilListeDesPatients,getModuleById(Modules::Accceuil),"Liste des patients"));
        listDetailModule.append(new DetailsModule(AcceuilAfficherListePatient,getModuleById(Modules::Accceuil),"Afficher liste des patients"));
        listDetailModule.append(new DetailsModule(AcceuilAjouterPatient,getModuleById(Modules::Accceuil),"Ajouter Patient"));
        listDetailModule.append(new DetailsModule(AcceuilModifierPatient,getModuleById(Modules::Accceuil),"Modifier Patient"));
        listDetailModule.append(new DetailsModule(AcceuilSupprimerPatient,getModuleById(Modules::Accceuil),"Supprimer Patient"));
        listDetailModule.append(new DetailsModule(AcceuilMenuProgrammationConsultation,getModuleById(Modules::Accceuil),"Menu Programmation Consulation"));
        listDetailModule.append(new DetailsModule(AcceuilAjouterConsultation,getModuleById(Modules::Accceuil),"Ajouter Consulation"));
        listDetailModule.append(new DetailsModule(AcceuilModifierConsultation,getModuleById(Modules::Accceuil),"Modifier Consultation"));
        listDetailModule.append(new DetailsModule(AcceuilSupprimerConsulation,getModuleById(Modules::Accceuil),"Supprimer Consulation"));
        listDetailModule.append(new DetailsModule(AcceuilListerConsulations,getModuleById(Modules::Accceuil),"Lister Consultations"));
        listDetailModule.append(new DetailsModule(AcceuilMenuProgrammationRendezVous,getModuleById(Modules::Accceuil),"Menu Programmation Rendez-Vous"));
        listDetailModule.append(new DetailsModule(AcceuilFixerRendezVous,getModuleById(Modules::Accceuil),"Ajouter Rendez-Vous"));
        listDetailModule.append(new DetailsModule(AcceuilModifierRendezVous,getModuleById(Modules::Accceuil),"Modifier Rendez-Vous"));
        listDetailModule.append(new DetailsModule(AcceuilSupprimerRendezVous,getModuleById(Modules::Accceuil),"Supprimer Rendez-Vous"));
        //listDetailModule.append(new DetailsModule(AcceuilListerExamens,getModuleById(Modules::Accceuil),"Reporter Rendez-Vous"));
        listDetailModule.append(new DetailsModule(AcceuilListerRendezVous,getModuleById(Modules::Accceuil),"Lister Rendez-Vous"));
        listDetailModule.append(new DetailsModule(AcceuilConfirmationRendezVous,getModuleById(Modules::Accceuil),"Confirmer Rendez-Vous"));
        listDetailModule.append(new DetailsModule(AcceuilMenuProgrammationExamen,getModuleById(Modules::Accceuil),"Menu Programmation Examens"));
        listDetailModule.append(new DetailsModule(AcceuilProgrammerExamen,getModuleById(Modules::Accceuil),"Programmer Examens"));
        listDetailModule.append(new DetailsModule(AcceuilModifierExamens,getModuleById(Modules::Accceuil),"Modifier Examen"));
        listDetailModule.append(new DetailsModule(AcceuilSupprimerExamens,getModuleById(Modules::Accceuil),"Supprimer Examen"));
        listDetailModule.append(new DetailsModule(AcceuilListerExamens,getModuleById(Modules::Accceuil),"Lister Examens"));
        listDetailModule.append(new DetailsModule(AcceuilVoirDetailsExamens,getModuleById(Modules::Accceuil),"Voir Details Examens"));
        listDetailModule.append(new DetailsModule(AcceuilMenuProgrammationAutresActes,getModuleById(Modules::Accceuil),"Menu Programmation Autres Actes"));
        listDetailModule.append(new DetailsModule(AcceuilAjouterAutresActes,getModuleById(Modules::Accceuil),"Ajouter Autres Actes"));
        listDetailModule.append(new DetailsModule(AcceuilModifierAutresActes,getModuleById(Modules::Accceuil),"Modifier Autres Actes"));
        listDetailModule.append(new DetailsModule(AcceuilSupprimerAutresActes,getModuleById(Modules::Accceuil),"Supprimer Autres Actes"));
        listDetailModule.append(new DetailsModule(AcceuilListerAutresActes,getModuleById(Modules::Accceuil),"Lister Autres Actes"));


        //Medecin
        listDetailModule.append(new DetailsModule(MedecinPatient,getModuleById(Modules::Medecin),"Patient"));
        listDetailModule.append(new DetailsModule(MedecinConsultation,getModuleById(Modules::Medecin),"Consultation"));
        listDetailModule.append(new DetailsModule(MedecinAfficherListeConsultations,getModuleById(Modules::Medecin),"Afficher liste Consultations"));
        listDetailModule.append(new DetailsModule(MedecinAjouterConsultation,getModuleById(Modules::Medecin),"Ajouter Consultation"));
        listDetailModule.append(new DetailsModule(MedecinModifierConsultation,getModuleById(Modules::Medecin),"Modifier Consultation"));
        listDetailModule.append(new DetailsModule(MedecinSupprimerConsultation,getModuleById(Modules::Medecin),"Supprimer Consultation"));
        listDetailModule.append(new DetailsModule(MedecinRendezVous,getModuleById(Modules::Medecin),"Rendez-Vous"));
        listDetailModule.append(new DetailsModule(MedecinStatsMedecin,getModuleById(Modules::Medecin),"Statistiques"));

        //detail hospitalisation
        listDetailModule.append(new DetailsModule(HospitalisationAjouterHospi,getModuleById(Modules::Hospitalisation),"Ajouter Hospitalistion"));
        listDetailModule.append(new DetailsModule(HospitalisationModifierHospi,getModuleById(Modules::Hospitalisation),"Modifier Hospitalisation"));
        listDetailModule.append(new DetailsModule(HospitalisationAfficherListeHospi,getModuleById(Modules::Hospitalisation),"Afficher liste Hosptalisation"));
        listDetailModule.append(new DetailsModule(HospitalisationSupprimerHispi,getModuleById(Modules::Hospitalisation),"Supprimer Hospitalisation"));
        listDetailModule.append(new DetailsModule(HospitalisationLibererPatient,getModuleById(Modules::Hospitalisation),"Liberer Hospitalisation"));

        //Bloc Operatoir
        listDetailModule.append(new DetailsModule(BlocOperatoireAjouterInterverntion,getModuleById(Modules::BlocOperatoire),"Ajouter Intervention"));
        listDetailModule.append(new DetailsModule(BlocOperatoireModifierIntervention,getModuleById(Modules::BlocOperatoire),"Modifier Intervention"));
        listDetailModule.append(new DetailsModule(BlocOperatoireAfficherListeIntervention,getModuleById(Modules::BlocOperatoire),"Afficher  liste Intervention"));
        listDetailModule.append(new DetailsModule(BlocOperatoireSupprimerIntervention,getModuleById(Modules::BlocOperatoire),"Supprimer Intervention"));
        listDetailModule.append(new DetailsModule(BlocOperatoireBonDeCommande,getModuleById(Modules::BlocOperatoire),"Rediger Bon de Commande"));
        listDetailModule.append(new DetailsModule(BlocOperatoireProtocoleDeSoins,getModuleById(Modules::BlocOperatoire),"Rediger Protocol de Soins"));
        listDetailModule.append(new DetailsModule(OphtalmologieAfficherListe,getModuleById(Modules::Ophtalmologie),"Afficher liste interventions"));

        //Pharmacie
        listDetailModule.append(new DetailsModule(PharmacieProduits,getModuleById(Modules::Pharmacie),"Produits"));
        listDetailModule.append(new DetailsModule(PharmacieVentes,getModuleById(Modules::Pharmacie),"Ventes"));
        listDetailModule.append(new DetailsModule(PharmacieStock,getModuleById(Modules::Pharmacie),"Stocks"));
        listDetailModule.append(new DetailsModule(PharmacieOrdonnances,getModuleById(Modules::Pharmacie),"Ordonnances"));
        listDetailModule.append(new DetailsModule(PharmacieBonDeCommandes,getModuleById(Modules::Pharmacie),"Bon de Commandes"));
        listDetailModule.append(new DetailsModule(PharmacieNouveauStock,getModuleById(Modules::Pharmacie),"Nouveau Stocks"));
        listDetailModule.append(new DetailsModule(PharmacieValidation,getModuleById(Modules::Pharmacie),"Validation de commande"));
        listDetailModule.append(new DetailsModule(PharmacieInventaire,getModuleById(Modules::Pharmacie),"Inventaire de produit"));
        listDetailModule.append(new DetailsModule(PharmacieListeDesVente,getModuleById(Modules::Pharmacie),"Liste des ventes"));
        listDetailModule.append(new DetailsModule(PharmacieRechercherFacture,getModuleById(Modules::Pharmacie),"Rechercher ticket de caisse"));
        listDetailModule.append(new DetailsModule(PharmacieEchangesDeStock,getModuleById(Modules::Pharmacie),"Echanges de stock"));

        // Encaissement
        listDetailModule.append(new DetailsModule(EncaissementPharmacie,getModuleById(Modules::Encaissement),"Pharamacie"));
        listDetailModule.append(new DetailsModule(EncaissementConsultation,getModuleById(Modules::Encaissement),"Consultation"));
        listDetailModule.append(new DetailsModule(EncaissementHospitalisation,getModuleById(Modules::Encaissement),"Hospitalisation"));
        listDetailModule.append(new DetailsModule(EncaissementDepotCaution,getModuleById(Modules::Encaissement),"Depot caution"));
        listDetailModule.append(new DetailsModule(EncaissementExamens,getModuleById(Modules::Encaissement),"Examens"));
        listDetailModule.append(new DetailsModule(EncaissementBlocOperatoire,getModuleById(Modules::Encaissement),"Bloc operatoire"));
        listDetailModule.append(new DetailsModule(EncaissementAutresActesMedicaux,getModuleById(Modules::Encaissement),"Actes Medicaux"));
        //listDetailModule.append(new DetailsModule(EncaissementJournalEncaissement,getModuleById(Modules::Encaissement),"Journal Encaissement"));

        //Personnel
        listDetailModule.append(new DetailsModule(PersonnelEnregistrerPersonnel,getModuleById(Modules::Personnel),"Enregistrer Personnel"));
        listDetailModule.append(new DetailsModule(PersonnelModifierPersonnel,getModuleById(Modules::Personnel),"Modifier Personnel"));
        listDetailModule.append(new DetailsModule(PersonnelAfficherListePersonnel,getModuleById(Modules::Personnel),"Afficher Liste Personnel"));
        listDetailModule.append(new DetailsModule(PersonnelSupprimerPersonnel,getModuleById(Modules::Personnel),"Supprimer Personnel"));
        listDetailModule.append(new DetailsModule(PersonnelReceptionDossier,getModuleById(Modules::Personnel),"Recption de Dossier"));
        listDetailModule.append(new DetailsModule(PersonnelImprimerRegistreEmployeur,getModuleById(Modules::Personnel),"Imprimer Registe Employeur"));
        listDetailModule.append(new DetailsModule(PersonnelImprimerContratTravail,getModuleById(Modules::Personnel),"Imprimer Contrat de Travail"));
        listDetailModule.append(new DetailsModule(PersonnelImprimerEtatDePaie,getModuleById(Modules::Personnel),"Imprimer Etat de Payement"));
        listDetailModule.append(new DetailsModule(PersonnelAccesssoireSalaire,getModuleById(Modules::Personnel),"Accessoir Salaire"));
        listDetailModule.append(new DetailsModule(PersonnelAjouterAccessoire,getModuleById(Modules::Personnel),"Ajouter"));
        listDetailModule.append(new DetailsModule(PersonnelAfficherListeAccessoire,getModuleById(Modules::Personnel),"Afficher liste Accessoir"));

        //Comptabilite
        listDetailModule.append(new DetailsModule(ComptabiliteSaisiesDepensesRecettes,getModuleById(Modules::Comptabilite),"Saisie des depenses & Recettes"));
        listDetailModule.append(new DetailsModule(ComptabiliteAjouterDepensesRecettes,getModuleById(Modules::Comptabilite),"Ajouter Depenses & Recettes"));
        listDetailModule.append(new DetailsModule(ComptabiliteModifierDepensesRecettes,getModuleById(Modules::Comptabilite),"Modifier Depenses & Recettes"));
        listDetailModule.append(new DetailsModule(ComptabiliteSupprimerDepensesRecettes,getModuleById(Modules::Comptabilite),"Surpprimer Depenses & Recettes"));
        listDetailModule.append(new DetailsModule(ComptabiliteAfficherListeDepensesRecettes,getModuleById(Modules::Comptabilite),"Afficher Liste Depenses & Recettes"));
        listDetailModule.append(new DetailsModule(ComptabiliteReglementFournisseur,getModuleById(Modules::Comptabilite),"Reglement Fournisseur"));
        listDetailModule.append(new DetailsModule(ComptabiliteBilanCompteExploitation,getModuleById(Modules::Comptabilite),"Bilan De Compte D'Exploitation"));
        listDetailModule.append(new DetailsModule(ComptabiliteJournalEncaissement,getModuleById(Modules::Comptabilite),"Journal Encaissement"));

        //Statistique
        listDetailModule.append(new DetailsModule(StatistiquesExamens,getModuleById(Modules::Statistiques),"Statistiques Examens "));
        listDetailModule.append(new DetailsModule(StatistiquesChirurgie,getModuleById(Modules::Statistiques),"Statistiques Chirugie "));
        listDetailModule.append(new DetailsModule(StatistiquesConsultations,getModuleById(Modules::Statistiques),"Statistiques Consultation"));
        //listDetailModule.append(new DetailsModule(4,getModuleById(Modules::Statistiques),"Liste des Utilisateur "));

        //Paramettre
/*
        listDetailModule.append(new DetailsModule(1,getModuleById(10),"Caisse"));
        listDetailModule.append(new DetailsModule(2,getModuleById(10),"Ajouter "));
        listDetailModule.append(new DetailsModule(3,getModuleById(10),"Modifier "));
        listDetailModule.append(new DetailsModule(4,getModuleById(10),"Supprimmer"));
        listDetailModule.append(new DetailsModule(5,getModuleById(10),"Examen"));
        listDetailModule.append(new DetailsModule(6,getModuleById(10),"Ajouter "));
        listDetailModule.append(new DetailsModule(7,getModuleById(10),"Modifier "));
        listDetailModule.append(new DetailsModule(8,getModuleById(10),"Supprimmer"));
        listDetailModule.append(new DetailsModule(9,getModuleById(10),"Comptabilite"));
        listDetailModule.append(new DetailsModule(10,getModuleById(10),"Ajouter "));
        listDetailModule.append(new DetailsModule(11,getModuleById(10),"Modifier "));
        listDetailModule.append(new DetailsModule(12,getModuleById(10),"Supprimmer"));
        listDetailModule.append(new DetailsModule(13,getModuleById(10),"Paramettre Global"));
        listDetailModule.append(new DetailsModule(14,getModuleById(10),"Ajouter "));
        listDetailModule.append(new DetailsModule(15,getModuleById(10),"Modifier "));
        listDetailModule.append(new DetailsModule(16,getModuleById(10),"Supprimmer"));
        listDetailModule.append(new DetailsModule(17,getModuleById(10),"Tarifs"));
        listDetailModule.append(new DetailsModule(18,getModuleById(10),"Ajouter "));
        listDetailModule.append(new DetailsModule(19,getModuleById(10),"Modifier "));
        listDetailModule.append(new DetailsModule(20,getModuleById(10),"Supprimmer"));

        //Sessions
        listDetailModule.append(new DetailsModule(1,getModuleById(11),"Demarrer une Session "));
        listDetailModule.append(new DetailsModule(2,getModuleById(11),"Arreter une Session "));

        //Utilisateur
        listDetailModule.append(new DetailsModule(1,getModuleById(12),"Ajouter "));
        listDetailModule.append(new DetailsModule(2,getModuleById(12),"Modifier "));
        listDetailModule.append(new DetailsModule(3,getModuleById(12),"Supprimmer"));
        listDetailModule.append(new DetailsModule(4,getModuleById(12),"Liste des Utilisateur "));
*/
        //Droit d'Utilissateur
//        listDetailModule.append(new DetailsModule(1,getModuleById(13),"Ajouter "));
//        listDetailModule.append(new DetailsModule(2,getModuleById(13),"Modifier "));
//        listDetailModule.append(new DetailsModule(3,getModuleById(13),"Supprimmer"));
//        listDetailModule.append(new DetailsModule(4,getModuleById(13),"Liste des Utilisateur "));

        /*listDetailModule.append(new DetailsModule(1,getModuleById(2),"Encaisser"));
        listDetailModule.append(new DetailsModule(2,getModuleById(2),"Panier lister"));
        listDetailModule.append(new DetailsModule(3,getModuleById(2),"Details vente"));
        listDetailModule.append(new DetailsModule(4,getModuleById(2),"Renvoi à la vente"));
        listDetailModule.append(new DetailsModule(5,getModuleById(2),"Imprimer ticket"));
        listDetailModule.append(new DetailsModule(6,getModuleById(2),"Status Bar"));

        listDetailModule.append(new DetailsModule(1,getModuleById(3),"Lister"));
        listDetailModule.append(new DetailsModule(2,getModuleById(3),"Détails"));
        listDetailModule.append(new DetailsModule(3,getModuleById(3),"Rechercher"));

        listDetailModule.append(new DetailsModule(1,getModuleById(4),"Liste produits"));
        listDetailModule.append(new DetailsModule(2,getModuleById(4),"Ajout commande"));
        listDetailModule.append(new DetailsModule(3,getModuleById(4),"Retirer commande"));
        listDetailModule.append(new DetailsModule(4,getModuleById(4),"Annuler commande"));
        listDetailModule.append(new DetailsModule(5,getModuleById(4),"Valider commande"));
        listDetailModule.append(new DetailsModule(6,getModuleById(4),"Liste détails commande"));

        listDetailModule.append(new DetailsModule(1,getModuleById(6),"Lister"));
        listDetailModule.append(new DetailsModule(2,getModuleById(6),"Ajouter"));
        listDetailModule.append(new DetailsModule(3,getModuleById(6),"Modifier"));
        listDetailModule.append(new DetailsModule(4,getModuleById(6),"Supprimer"));

        listDetailModule.append(new DetailsModule(1,getModuleById(7),"Lister"));
        listDetailModule.append(new DetailsModule(2,getModuleById(7),"Ajouter"));
        listDetailModule.append(new DetailsModule(3,getModuleById(7),"Modifier"));
        listDetailModule.append(new DetailsModule(4,getModuleById(7),"Supprimer"));

        listDetailModule.append(new DetailsModule(1,getModuleById(8),"Lister"));
        listDetailModule.append(new DetailsModule(2,getModuleById(8),"Ajouter"));
        listDetailModule.append(new DetailsModule(3,getModuleById(8),"Modifier"));
        listDetailModule.append(new DetailsModule(4,getModuleById(8),"Supprimer"));
        listDetailModule.append(new DetailsModule(5,getModuleById(8),"Voir total"));

        listDetailModule.append(new DetailsModule(1,getModuleById(9),"Rechercher"));
        listDetailModule.append(new DetailsModule(2,getModuleById(9),"Liste"));
        listDetailModule.append(new DetailsModule(3,getModuleById(9),"Details"));
        listDetailModule.append(new DetailsModule(4,getModuleById(9),"Voir total encaissement"));

        listDetailModule.append(new DetailsModule(1,getModuleById(10),"Etape 1"));
        listDetailModule.append(new DetailsModule(2,getModuleById(10),"Etape 2"));
        listDetailModule.append(new DetailsModule(3,getModuleById(10),"Etape 3"));
        listDetailModule.append(new DetailsModule(4,getModuleById(10),"Etape 4"));
        listDetailModule.append(new DetailsModule(5,getModuleById(10),"Etape 5"));

        listDetailModule.append(new DetailsModule(1,getModuleById(11),"Liste des sessions"));
        listDetailModule.append(new DetailsModule(2,getModuleById(11),"Demarrer session"));
        listDetailModule.append(new DetailsModule(3,getModuleById(11),"Arrêter session"));

        listDetailModule.append(new DetailsModule(1,getModuleById(12),"Ajouter"));
        listDetailModule.append(new DetailsModule(2,getModuleById(12),"Modifier"));
        listDetailModule.append(new DetailsModule(3,getModuleById(12),"Lister"));

        listDetailModule.append(new DetailsModule(1,getModuleById(13),"Droits"));
        */







        /*listDetailModule.append(new DetailsModule(7,getModuleById(2),"Encaisser"));
        listDetailModule.append(new DetailsModule(8,getModuleById(2),"Panier lister"));
        listDetailModule.append(new DetailsModule(9,getModuleById(2),"Details vente"));
        listDetailModule.append(new DetailsModule(10,getModuleById(2),"Renvoi à la vente"));
        listDetailModule.append(new DetailsModule(11,getModuleById(2),"Imprimer ticket"));
        listDetailModule.append(new DetailsModule(12,getModuleById(2),"Status Bar"));

        listDetailModule.append(new DetailsModule(13,getModuleById(3),"Lister"));
        listDetailModule.append(new DetailsModule(14,getModuleById(3),"Détails"));
        listDetailModule.append(new DetailsModule(15,getModuleById(3),"Rechercher"));

        listDetailModule.append(new DetailsModule(16,getModuleById(4),"Liste produits"));
        listDetailModule.append(new DetailsModule(17,getModuleById(4),"Ajout commande"));
        listDetailModule.append(new DetailsModule(18,getModuleById(4),"Retirer commande"));
        listDetailModule.append(new DetailsModule(19,getModuleById(4),"Annuler commande"));
        listDetailModule.append(new DetailsModule(20,getModuleById(4),"Valider commande"));
        listDetailModule.append(new DetailsModule(21,getModuleById(4),"Liste détails commande"));

        listDetailModule.append(new DetailsModule(22,getModuleById(6),"Lister"));
        listDetailModule.append(new DetailsModule(23,getModuleById(6),"Ajouter"));
        listDetailModule.append(new DetailsModule(24,getModuleById(6),"Modifier"));
        listDetailModule.append(new DetailsModule(25,getModuleById(6),"Supprimer"));

        listDetailModule.append(new DetailsModule(26,getModuleById(7),"Lister"));
        listDetailModule.append(new DetailsModule(26,getModuleById(7),"Ajouter"));
        listDetailModule.append(new DetailsModule(26,getModuleById(7),"Modifier"));
        listDetailModule.append(new DetailsModule(26,getModuleById(7),"Supprimer"));

        listDetailModule.append(new DetailsModule(27,getModuleById(8),"Lister"));
        listDetailModule.append(new DetailsModule(28,getModuleById(8),"Ajouter"));
        listDetailModule.append(new DetailsModule(29,getModuleById(8),"Modifier"));
        listDetailModule.append(new DetailsModule(30,getModuleById(8),"Supprimer"));
        listDetailModule.append(new DetailsModule(31,getModuleById(8),"Voir total"));

        listDetailModule.append(new DetailsModule(32,getModuleById(9),"Rechercher"));
        listDetailModule.append(new DetailsModule(33,getModuleById(9),"Liste"));
        listDetailModule.append(new DetailsModule(34,getModuleById(9),"Details"));
        listDetailModule.append(new DetailsModule(35,getModuleById(9),"Voir total encaissement"));

        listDetailModule.append(new DetailsModule(36,getModuleById(10),"Etape 1"));
        listDetailModule.append(new DetailsModule(37,getModuleById(10),"Etape 2"));
        listDetailModule.append(new DetailsModule(38,getModuleById(10),"Etape 3"));
        listDetailModule.append(new DetailsModule(39,getModuleById(10),"Etape 4"));
        listDetailModule.append(new DetailsModule(40,getModuleById(10),"Etape 5"));

        listDetailModule.append(new DetailsModule(41,getModuleById(11),"Liste des sessions"));
        listDetailModule.append(new DetailsModule(42,getModuleById(11),"Demarrer session"));
        listDetailModule.append(new DetailsModule(43,getModuleById(11),"Arrêter session"));

        listDetailModule.append(new DetailsModule(44,getModuleById(12),"Ajouter"));
        listDetailModule.append(new DetailsModule(45,getModuleById(12),"Modifier"));
        listDetailModule.append(new DetailsModule(46,getModuleById(12),"Lister"));

        listDetailModule.append(new DetailsModule(47,getModuleById(13),"Droits"));*/

        listDetailModule.append(new DetailsModule(ParametrageCaisse,getModuleById(Modules::Parametrage),"Caisse"));
        listDetailModule.append(new DetailsModule(ParametrageAjouterCaisse,getModuleById(Modules::Parametrage),"Ajouter caisse "));
        listDetailModule.append(new DetailsModule(ParametrageModifierCaisse,getModuleById(Modules::Parametrage),"Modifier caisse "));
        listDetailModule.append(new DetailsModule(ParametrageSupprimerCaisse,getModuleById(Modules::Parametrage),"Supprimmer caisse"));
        listDetailModule.append(new DetailsModule(ParametrageExamen,getModuleById(Modules::Parametrage),"Examen"));
        listDetailModule.append(new DetailsModule(ParametrageAjouterExamen,getModuleById(Modules::Parametrage),"Ajouter examen"));
        listDetailModule.append(new DetailsModule(ParametrageModifierExamen,getModuleById(Modules::Parametrage),"Modifier examen"));
        listDetailModule.append(new DetailsModule(ParametrageSupprimerCaisse,getModuleById(Modules::Parametrage),"Supprimer caisse"));
        listDetailModule.append(new DetailsModule(ParametrageChapitre,getModuleById(Modules::Parametrage),"Chapitre"));
        listDetailModule.append(new DetailsModule(ParametrageChapitre,getModuleById(Modules::Parametrage),"Ajouter chapitre"));
        listDetailModule.append(new DetailsModule(ParametrageModifierChapitre,getModuleById(Modules::Parametrage),"Modifier chapitre"));
        listDetailModule.append(new DetailsModule(ParametrageSupprimerChapitre,getModuleById(Modules::Parametrage),"Supprimer chapitre"));
        listDetailModule.append(new DetailsModule(ParametrageParamGlobaux,getModuleById(Modules::Parametrage),"Parametre Globaux"));
        listDetailModule.append(new DetailsModule(ParametrageAjouterParam,getModuleById(Modules::Parametrage),"Ajouter param."));
        listDetailModule.append(new DetailsModule(ParametrageModifierParam,getModuleById(Modules::Parametrage),"Modifier param."));
        listDetailModule.append(new DetailsModule(ParametrageSupprimerParam,getModuleById(Modules::Parametrage),"Supprimer param."));
        listDetailModule.append(new DetailsModule(ParametrageTarifs,getModuleById(Modules::Parametrage),"Tarifs"));
        listDetailModule.append(new DetailsModule(ParametrageAjouterTarif,getModuleById(Modules::Parametrage),"Ajouter tarif"));
        listDetailModule.append(new DetailsModule(ParametrageModifierTarif,getModuleById(Modules::Parametrage),"Modifier tarif"));
        listDetailModule.append(new DetailsModule(ParametrageSupprimerTarif,getModuleById(Modules::Parametrage),"Supprimer tarif"));

        //Securité
        listDetailModule.append(new DetailsModule(SecuriteSessions,getModuleById(Modules::Securite),"Sessions"));
        listDetailModule.append(new DetailsModule(SecuriteDemarrerSession,getModuleById(Modules::Securite),"Demarrer une Session "));
        listDetailModule.append(new DetailsModule(SecuriteArreterSession,getModuleById(Modules::Securite),"Arreter une Session "));
        listDetailModule.append(new DetailsModule(SecuriteUtilisateurs,getModuleById(Modules::Securite),"Utilisateurs"));
        listDetailModule.append(new DetailsModule(SecuriteAjouterUtilisateur,getModuleById(Modules::Securite),"Ajouter utilisateur"));
        listDetailModule.append(new DetailsModule(SecuriteModifierUtilisateur,getModuleById(Modules::Securite),"Modifier utilisateur"));
        listDetailModule.append(new DetailsModule(SecuriteSupprimerUtilisateur,getModuleById(Modules::Securite),"Supprimer utilisateur"));
        listDetailModule.append(new DetailsModule(SecuriteListeUtilisateurs,getModuleById(Modules::Securite),"Liste des Utilisateur "));
        listDetailModule.append(new DetailsModule(SecuriteGroupesUtilisateurs,getModuleById(Modules::Securite),"Groupes utilisateurs"));
        listDetailModule.append(new DetailsModule(SecuriteAffecterGroupe,getModuleById(Modules::Securite),"Affecter groupe"));
        listDetailModule.append(new DetailsModule(SecuriteModifierAffectation,getModuleById(Modules::Securite),"Modifier affectation"));
        listDetailModule.append(new DetailsModule(SecuriteListeUtilisateurs,getModuleById(Modules::Securite),"Lister utilisateurs"));
        listDetailModule.append(new DetailsModule(SecuriteDroitsAccess,getModuleById(Modules::Securite),"Droits d'accès"));
        listDetailModule.append(new DetailsModule(SecuriteAffecterDroits,getModuleById(Modules::Securite),"Affecter droits"));
        listDetailModule.append(new DetailsModule(SecuriteModifierDroits,getModuleById(Modules::Securite),"Modifier droits"));
        listDetailModule.append(new DetailsModule(SecuriteListerGroupesUtilisateurs,getModuleById(Modules::Securite),"Lister groupes utilisateurs"));
    }

    Module *ModuleManager::getModuleById(const int &id)
    {
        for(Module* m : listModule){
            if(m->getIdModule() == id){
                return m;
            }
        }
        return new Module();
    }

    DetailsModule *ModuleManager::getDetailModuleById(const int &id)
    {
        for(DetailsModule* m : listDetailModule){
            if(m->getIdDetail() == id){
                return m;
            }
        }
        return new DetailsModule();
    }

    Module *ModuleManager::getModuleByName(const QString &name)
    {
        for(Module* m : listModule){
            if(m->getIntitule() == name){
                return m;
            }
        }
        return new Module();
    }

    DetailsModule *ModuleManager::getDetailModuleByName(const QString &name)
    {
        for(DetailsModule* m : listDetailModule){
            if(m->getIntitule() == name){
                return m;
            }
        }
        return new DetailsModule();
    }

    QList<Module *> ModuleManager::getListModule() const
    {
        return listModule;
    }

    void ModuleManager::setListModule(const QList<Module *> &value)
    {
        listModule = value;
    }

    QList<DetailsModule *> ModuleManager::getListDetailModule() const
    {
        return listDetailModule;
    }

    void ModuleManager::setListDetailModule(const QList<DetailsModule *> &value)
    {
        listDetailModule = value;
    }
}
