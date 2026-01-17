import { useState, useEffect } from 'react';
import { getCharactersByUniverse } from '../services/sparqlService';
import './CharactersList.css';

export default function CharactersList({ universeUri }) {
    const [characters, setCharacters] = useState([]);
    const [loading, setLoading] = useState(true);
    const [filter, setFilter] = useState('all');

    useEffect(() => {
        async function loadCharacters() {
            try {
                const data = await getCharactersByUniverse(universeUri);
                const results = data.results.bindings.map(b => ({
                    uri: b.character.value,
                    name: b.name.value,
                    type: b.type?.value || 'Character',
                    description: b.description?.value || ''
                }));
                setCharacters(results);
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

    // Filtro personaggi per tipo
    const filteredCharacters = characters.filter(char => {
        if (filter === 'all') return true;
        return char.type.includes(filter);
    });

    // Conta tipi
    const typeCounts = {
        all: characters.length,
        Protagonist: characters.filter(c => c.type.includes('Protagonist')).length,
        Alleato: characters.filter(c => c.type.includes('Alleato')).length,
        Antagonist: characters.filter(c => c.type.includes('Antagonist')).length,
        Mentor: characters.filter(c => c.type.includes('Mentor')).length
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
                {typeCounts.Protagonist > 0 && (
                    <button
                        className={`filter-btn ${filter === 'Protagonist' ? 'active' : ''}`}
                        onClick={() => setFilter('Protagonist')}
                    >
                        Protagonisti ({typeCounts.Protagonist})
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
                {typeCounts.Antagonist > 0 && (
                    <button
                        className={`filter-btn ${filter === 'Antagonist' ? 'active' : ''}`}
                        onClick={() => setFilter('Antagonist')}
                    >
                        Antagonisti ({typeCounts.Antagonist})
                    </button>
                )}
                {typeCounts.Mentor > 0 && (
                    <button
                        className={`filter-btn ${filter === 'Mentor' ? 'active' : ''}`}
                        onClick={() => setFilter('Mentor')}
                    >
                        Mentori ({typeCounts.Mentor})
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
                        <div key={character.uri} className="character-card">
                            <div className="character-header">
                                <h3 className="character-name">{character.name}</h3>
                                <span className="character-type">{character.type.split('#').pop()}</span>
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