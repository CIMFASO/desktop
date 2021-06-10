#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "models/module.h"
#include "models/detailsmodule.h"
#include <QList>

namespace Model {


class ModuleManager
{
public:
    ModuleManager();
    ~ModuleManager(){
        for(Module *m : listModule){
            delete m;
        }

        for(DetailsModule *d : listDetailModule){
            delete d;
        }
    };
    Module *getModuleById(const int &id);
    DetailsModule *getDetailModuleById(const int &id);
    Module *getModuleByName(const QString &name);
    DetailsModule *getDetailModuleByName(const QString &name);

    QList<Module *> getListModule() const;
    void setListModule(const QList<Module *> &value);

    QList<DetailsModule *> getListDetailModule() const;
    void setListDetailModule(const QList<DetailsModule *> &value);

    enum Modules{
        Accceuil = 1,
        Medecin,
        Hospitalisation,
        BlocOperatoire,
        Pharmacie,
        Encaissement,
        Personnel,
        Comptabilite,
        Statistiques,
        Parametrage,
        Securite,
        Ophtalmologie
    };
    enum Acceuil{
        AcceuilListeDesPatients = 101,
        AcceuilAfficherListePatient ,
        AcceuilAjouterPatient,
        AcceuilModifierPatient,
        AcceuilSupprimerPatient,
        AcceuilMenuProgrammationConsultation,
        AcceuilMenuProgrammationRendezVous,
        AcceuilMenuProgrammationExamen,
        AcceuilMenuProgrammationAutresActes,
        AcceuilConfirmationRendezVous,
        AcceuilFixerRendezVous,
        AcceuilModifierRendezVous,
        AcceuilSupprimerRendezVous,
        AcceuilListerRendezVous,
        AcceuilAjouterConsultation,
        AcceuilModifierConsultation,
        AcceuilSupprimerConsulation,
        AcceuilListerConsulations,
        AcceuilProgrammerExamen,
        AcceuilModifierExamens,
        AcceuilSupprimerExamens,
        AcceuilListerExamens,
        AcceuilVoirDetailsExamens,
        AcceuilAjouterAutresActes,
        AcceuilModifierAutresActes,
        AcceuilSupprimerAutresActes,
        AcceuilListerAutresActes
    };

    enum Medecin{
        MedecinPatient = 201,
        MedecinConsultation,
        MedecinAfficherListeConsultations,
        MedecinAjouterConsultation,
        MedecinModifierConsultation,
        MedecinSupprimerConsultation,
        MedecinRendezVous,
        MedecinStatsMedecin
    };

    enum Hospitalisation{
        HospitalisationAjouterHospi = 301,
        HospitalisationModifierHospi,
        HospitalisationAfficherListeHospi,
        HospitalisationSupprimerHispi,
        HospitalisationLibererPatient
    };
    enum BlocOperatoire{
        BlocOperatoireAjouterInterverntion = 401,
        BlocOperatoireModifierIntervention,
        BlocOperatoireAfficherListeIntervention,
        BlocOperatoireSupprimerIntervention,
        BlocOperatoireBonDeCommande,
        BlocOperatoireProtocoleDeSoins
    };
    enum Ophtalmologie{
        OphtalmologieAfficherListe = 1201
    };
    enum Pharmacie{
        PharmacieProduits = 501,
        PharmacieVentes,
        PharmacieStock,
        PharmacieOrdonnances,
        PharmacieBonDeCommandes,
        PharmacieNouveauStock,
        PharmacieValidation,
        PharmacieInventaire,
        PharmacieListeDesVente,
        PharmacieRechercherFacture,
        PharmacieEchangesDeStock
    };

    enum Encaissement{
        EncaissementPharmacie = 601,
        EncaissementConsultation,
        EncaissementHospitalisation,
        EncaissementDepotCaution,
        EncaissementExamens,
        EncaissementBlocOperatoire,
        EncaissementAutresActesMedicaux,
        EncaissementJournalEncaissement
    };

    enum Personnel{
        PersonnelEnregistrerPersonnel = 701,
        PersonnelModifierPersonnel,
        PersonnelAfficherListePersonnel,
        PersonnelSupprimerPersonnel,
        PersonnelReceptionDossier,
        PersonnelImprimerEtatDePaie,
        PersonnelImprimerRegistreEmployeur,
        PersonnelImprimerContratTravail,
        PersonnelAccesssoireSalaire,
        PersonnelAjouterAccessoire,
        PersonnelAfficherListeAccessoire,
        PersonnelPayementPersonnel
    };

    enum Comptabilite{
        ComptabiliteSaisiesDepensesRecettes = 801,
        ComptabiliteAjouterDepensesRecettes,
        ComptabiliteModifierDepensesRecettes,
        ComptabiliteSupprimerDepensesRecettes,
        ComptabiliteAfficherListeDepensesRecettes,
        ComptabiliteReglementFournisseur,
        ComptabiliteBilanCompteExploitation,
        ComptabiliteJournalEncaissement
    };

    enum Statitiques{
        StatistiquesExamens = 901,
        StatistiquesChirurgie,
        StatistiquesConsultations
    };

    enum Parametrage{
        ParametrageCaisse = 1001,
        ParametrageAjouterCaisse,
        ParametrageModifierCaisse,
        ParametrageSupprimerCaisse,
        ParametrageExamen,
        ParametrageAjouterExamen,
        ParametrageModifierExamen,
        ParametrageSupprimerExamen,
        ParametrageChapitre,
        ParametrageAjouterChapitre,
        ParametrageModifierChapitre,
        ParametrageSupprimerChapitre,
        ParametrageParamGlobaux,
        ParametrageAjouterParam,
        ParametrageModifierParam,
        ParametrageSupprimerParam,
        ParametrageTarifs,
        ParametrageAjouterTarif,
        ParametrageModifierTarif,
        ParametrageSupprimerTarif
    };

    enum Securite{
        SecuriteSessions = 1101,
        SecuriteDemarrerSession,
        SecuriteArreterSession,
        SecuriteUtilisateurs,
        SecuriteAjouterUtilisateur,
        SecuriteModifierUtilisateur,
        SecuriteSupprimerUtilisateur,
        SecuriteListeDesUtilisateurs,
        SecuriteGroupesUtilisateurs,
        SecuriteAffecterGroupe,
        SecuriteModifierAffectation,
        SecuriteListeUtilisateurs,
        SecuriteDroitsAccess,
        SecuriteAffecterDroits,
        SecuriteModifierDroits,
        SecuriteListerGroupesUtilisateurs
    };

private:
    QList <Module*> listModule;
    QList <DetailsModule*> listDetailModule;
};
}
#endif // MODULEMANAGER_H
