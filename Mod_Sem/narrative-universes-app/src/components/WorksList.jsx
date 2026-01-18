import { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { getWorksByUniverse } from '../services/sparqlService';
import './WorksList.css';

export default function WorksList({ universeUri }) {
    const [works, setWorks] = useState([]);
    const [loading, setLoading] = useState(true);
    const [filter, setFilter] = useState('all');

    const navigate = useNavigate();

    useEffect(() => {
        async function loadWorks() {
            try {
                const data = await getWorksByUniverse(universeUri);
                const results = data.results.bindings.map(b => ({
                    uri: b.work.value,
                    title: b.title.value,
                    type: (() => {
                        const t = b.type?.value || 'NarrativeWork';
                        return t === 'TelevisionSeries' ? 'TVSeries' : t;
                    })(),
                    year: b.year?.value || null,
                    runtime: b.runtime?.value || null,
                    pages: b.pages?.value || null
                }));
                setWorks(results);
            } catch (err) {
                console.error('Error loading works:', err);
            } finally {
                setLoading(false);
            }
        }

        loadWorks();
    }, [universeUri]);

    if (loading) {
        return (
            <div className="loading-state">
                <div className="spinner"></div>
                <p>Caricamento opere...</p>
            </div>
        );
    }

    const filtered = works.filter(w => {
        if (filter === 'all') return true;
        return w.type === filter;
    });

    const typeCounts = {
        all: works.length,
        Book: works.filter(w => w.type === 'Book').length,
        Movie: works.filter(w => w.type === 'Movie').length,
        TVSeries: works.filter(w => w.type === 'TVSeries').length
    };

    return (
        <div className="works-list">
            <div className="filters">
                <button className={filter === 'all' ? 'active' : ''} onClick={() => setFilter('all')}>
                    Tutte ({typeCounts.all})
                </button>

                {typeCounts.Book > 0 && (
                    <button className={filter === 'Book' ? 'active' : ''} onClick={() => setFilter('Book')}>
                        Libri ({typeCounts.Book})
                    </button>
                )}

                {typeCounts.Movie > 0 && (
                    <button className={filter === 'Movie' ? 'active' : ''} onClick={() => setFilter('Movie')}>
                        Film ({typeCounts.Movie})
                    </button>
                )}

                <button className={filter === 'TVSeries' ? 'active' : ''} onClick={() => setFilter('TVSeries')}>
                    Serie TV ({typeCounts.TVSeries})
                </button>
            </div>

            <div className="cards-grid">
                {filtered.length === 0 ? (
                    <div className="empty-state">Nessuna opera trovata</div>
                ) : (
                    filtered.map(work => (
                        <div
                            key={work.uri}
                            className="work-card"
                            onClick={() =>
                                navigate(`/entity?uri=${encodeURIComponent(work.uri)}`)
                            }
                        >
                            <h3 className="work-title">{work.title}</h3>
                            <span className="work-type">{work.type}</span>

                            <div className="work-info">
                                {work.year && <p><strong>Anno:</strong> {work.year}</p>}
                                {work.runtime && <p><strong>Durata:</strong> {work.runtime} min</p>}
                                {work.pages && <p><strong>Pagine:</strong> {work.pages}</p>}
                            </div>
                        </div>
                    ))
                )}
            </div>
        </div>
    );
}
