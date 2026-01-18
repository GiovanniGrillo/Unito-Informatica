import { useEffect, useState } from 'react';
import { useSearchParams, useNavigate } from 'react-router-dom';
import { getEntityDetails } from '../services/sparqlService';
import './EntityDetails.css';

export default function EntityDetails() {
    const [params] = useSearchParams();
    const uri = params.get('uri');
    const navigate = useNavigate();

    const [entity, setEntity] = useState(null);

    useEffect(() => {
        async function load() {
            const data = await getEntityDetails(uri);
            setEntity(data);
        }
        load();
    }, [uri]);

    if (!entity) return <div className="loading-state">Caricamento...</div>;

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
                <span className="type">{entity.type}</span>

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
