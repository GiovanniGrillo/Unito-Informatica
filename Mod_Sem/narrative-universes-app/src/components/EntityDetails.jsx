import { useEffect, useState, useCallback } from 'react';
import { useSearchParams, useNavigate } from 'react-router-dom';
import { getEntityDetails } from '../services/sparqlService';
import '../styles/EntityDetails.css';

export default function EntityDetails() {
    const [params] = useSearchParams();
    const uri = params.get('uri');
    const navigate = useNavigate();

    const [entity, setEntity] = useState(null);
    const [error, setError] = useState(null);

    const fetchEntity = useCallback(async () => {
        try {
            const data = await getEntityDetails(uri);
            setEntity(data);
            setError(null);
        } catch (e) {
            setError(e.message || 'Errore nel caricamento dei dettagli');
        }
    }, [uri]);

    useEffect(() => {
        const id = setTimeout(() => {
            fetchEntity();
        }, 0);
        return () => clearTimeout(id);
    }, [fetchEntity]);

    if (!entity && !error) return (
        <div className="loading-state">
            <div className="spinner"></div>
            <p>Caricamento dettagli...</p>
        </div>
    );

    if (error) {
        return (
            <div className="error">
                <h2>Errore</h2>
                <p>{error}</p>
                <p className="error-hint">
                    Assicurati che GraphDB e il proxy server siano attivi
                </p>
                <button className="back-button" onClick={fetchEntity}>Riprova</button>
            </div>
        );
    }

    const renderList = (title, items) => {
        if (!items || items.length === 0) return null;
        return (
            <div className="section">
                <h3>{title}</h3>
                <ul>
                    {items.map(i => (
                        <li
                            key={i}
                            className="clickable"
                            onClick={() => navigate(`/entity?uri=${encodeURIComponent(i)}`)}
                        >
                            {i.split('#').pop()}
                        </li>
                    ))}
                </ul>
            </div>
        );
    };

    return (
        <>
            <header className="header">
                <button className="back-button" onClick={() => navigate(-1)}>
                    <span className="back-icon" aria-hidden="true" />
                    <span className="sr-only">Torna indietro</span>
                </button>
            </header>

            <div className="entity-details">
                <h1>{entity.label}</h1>
                {(() => {
                    const typeLabels = {
                        Character: "Personaggio",
                        Location: "Luogo",
                        NarrativeWork: "Opera Narrativa",
                        Object: "Oggetto",
                        Organization: "Organizzazione",
                        School: "Scuola",
                        SafePlace: "Luogo Sicuro",
                        DangerZone: "Zona Pericolosa",
                        LiminalSpace: "Spazio di Confine",
                        Ability: "Abilità",
                        MagicalAbility: "Abilità Magica",
                        HumanCharacter: "Personaggio",
                        NonHumanCharacter: "Non Umano",
                        HybridCharacter: "Ibrido",
                        Book: "Libro",
                        Movie: "Film",
                        TelevisionSeries: "Serie TV"
                    };
                    return (
                        <span className="type">{typeLabels[entity.type] || entity.type}</span>
                    );
                })()}

                {entity.description && (
                    <p className="description">{entity.description}</p>
                )}

                {renderList("Alleati", entity.allies)}
                {renderList("Nemici", entity.enemies)}
                {renderList("Mentori", entity.mentors)}
                {renderList("Allievi", entity.students)}
                {renderList("Oggetti posseduti", entity.objects)}
                {renderList("Abilità", entity.abilities)}
                {renderList("Opere", entity.works)}
                {renderList("Organizzazioni", entity.organizations)}
                {renderList("Luoghi ambientazione", entity.locations)}
                {renderList("Prequel", entity.prequels)}
                {renderList("Sequel", entity.sequels)}
                {renderList("Adattamenti", entity.adaptations)}

                {renderList("Posseduto da", entity.owners)}
                {renderList("Abilità conferite", entity.abilities)}

                {((entity.powerType && entity.powerType.length > 0) || entity.canBeDestroyed !== null) && (
                    <div className="section">
                        <h3>Attributi</h3>
                        {entity.powerType && (
                            <p>Tipo di potere: {entity.powerType.split('#').pop()}</p>
                        )}
                        {entity.canBeDestroyed !== null && (
                            <p>Può essere distrutto: {entity.canBeDestroyed === 'true' ? 'Sì' : 'No'}</p>
                        )}
                    </div>
                )}

                {entity.narrativeFunction && (
                    <div className="section">
                        <h3>Funzione narrativa</h3>
                        <p>{entity.narrativeFunction}</p>
                    </div>
                )}

                {entity.dangerLevel && (
                    <div className="section">
                        <h3>Livello di pericolo</h3>
                        <p>{entity.dangerLevel}</p>
                    </div>
                )}
            </div>
        </>
    );
}
