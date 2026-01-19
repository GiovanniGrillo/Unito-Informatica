import { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { getCharactersByUniverse } from '../services/sparqlService';
import '../styles/CharactersList.css';

export default function CharactersList({ universeUri }) {
    const [characters, setCharacters] = useState([]);
    const [loading, setLoading] = useState(true);
    const [filter, setFilter] = useState('all');

    const navigate = useNavigate();

    // Funzione per pulire e rinominare i ruoli
    function cleanRoles(types) {
        const blacklist = ["Character", "HUMANCHARACTER", "HumanCharacter"];
        const rename = {
            Protagonist: "Protagonista",
            Alleato: "Alleato",
            Antagonist: "Antagonista",
            Mentor: "Mentore",
            NonHumanCharacter: "Non Umano",
            NONHUMANCHARACTER: "Non Umano",
            HybridCharacter: "Ibrido"
        };

        return types
            .filter(t => !blacklist.includes(t))
            .map(t => rename[t] || t);
    }

    useEffect(() => {
        async function loadCharacters() {
            try {
                const data = await getCharactersByUniverse(universeUri);
                const raw = data.results.bindings;

                const grouped = {};

                raw.forEach(b => {
                    const uri = b.character.value;

                    if (!grouped[uri]) {
                        grouped[uri] = {
                            uri,
                            name: b.name.value,
                            description: b.description?.value || "",
                            types: new Set()
                        };
                    }

                    const role = b.type?.value?.split('#').pop() || "Character";
                    grouped[uri].types.add(role);
                });

                const finalCharacters = Object.values(grouped).map(c => ({
                    ...c,
                    types: cleanRoles(Array.from(c.types))
                }));

                setCharacters(finalCharacters);
            } catch (error) {
                console.error('Error loading characters:', error);
            } finally {
                setLoading(false);
            }
        }

        loadCharacters();
    }, [universeUri]);

    if (loading) {
        return (
            <div className="loading-state">
                <div className="spinner"></div>
                <p>Caricamento personaggi...</p>
            </div>
        );
    }

    const filteredCharacters =
        filter === 'all'
            ? characters
            : characters.filter(c => c.types.includes(filter));

    const typeCounts = {
        all: characters.length,
        Protagonista: characters.filter(c => c.types.includes('Protagonista')).length,
        Alleato: characters.filter(c => c.types.includes('Alleato')).length,
        Antagonista: characters.filter(c => c.types.includes('Antagonista')).length,
        Mentore: characters.filter(c => c.types.includes('Mentore')).length
    };

    return (
        <div className="characters-list">
            <div className="filters">
                <button
                    className={`filter-btn ${filter === 'all' ? 'active' : ''}`}
                    onClick={() => setFilter('all')}
                >
                    Tutti ({typeCounts.all})
                </button>

                {typeCounts.Protagonista > 0 && (
                    <button
                        className={`filter-btn ${filter === 'Protagonista' ? 'active' : ''}`}
                        onClick={() => setFilter('Protagonista')}
                    >
                        Protagonisti ({typeCounts.Protagonista})
                    </button>
                )}

                {typeCounts.Alleato > 0 && (
                    <button
                        className={`filter-btn ${filter === 'Alleato' ? 'active' : ''}`}
                        onClick={() => setFilter('Alleato')}
                    >
                        Alleati ({typeCounts.Alleato})
                    </button>
                )}

                {typeCounts.Antagonista > 0 && (
                    <button
                        className={`filter-btn ${filter === 'Antagonista' ? 'active' : ''}`}
                        onClick={() => setFilter('Antagonista')}
                    >
                        Antagonisti ({typeCounts.Antagonista})
                    </button>
                )}

                {typeCounts.Mentore > 0 && (
                    <button
                        className={`filter-btn ${filter === 'Mentore' ? 'active' : ''}`}
                        onClick={() => setFilter('Mentore')}
                    >
                        Mentori ({typeCounts.Mentore})
                    </button>
                )}
            </div>

            <div className="cards-grid">
                {filteredCharacters.length === 0 ? (
                    <div className="empty-state">
                        <p>Nessun personaggio trovato</p>
                    </div>
                ) : (
                    filteredCharacters.map(character => (
                        <div
                            key={character.uri}
                            className="character-card"
                            onClick={() =>
                                navigate(`/entity?uri=${encodeURIComponent(character.uri)}`)
                            }
                        >
                            <div className="character-header">
                                <h3 className="character-name">{character.name}</h3>

                                <div className="character-tags">
                                    {character.types.map(role => (
                                        <span key={role} className="tag">{role}</span>
                                    ))}
                                </div>
                            </div>

                            {character.description && (
                                <p className="character-description">{character.description}</p>
                            )}
                        </div>
                    ))
                )}
            </div>
        </div>
    );
}
