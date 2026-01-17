import { useState } from 'react';
import CharactersList from './CharactersList';
import LocationsList from './LocationsList';
import WorksList from './WorksList';
import './UniverseDashboard.css';

export default function UniverseDashboard({ universe }) {
    const [activeTab, setActiveTab] = useState('characters');

    const tabs = [
        { id: 'characters', label: 'Personaggi', count: universe.characters },
        { id: 'locations', label: 'Luoghi', count: universe.locations },
        { id: 'works', label: 'Opere', count: universe.works }
    ];

    return (
        <div className="dashboard">
            <div className="dashboard-header">
                <div className="universe-info">
                    <h1 className="universe-title">{universe.name}</h1>
                    <div className="universe-meta">
                        <span className="meta-item">{universe.characters} Personaggi</span>
                        <span className="meta-separator">•</span>
                        <span className="meta-item">{universe.locations} Luoghi</span>
                        <span className="meta-separator">•</span>
                        <span className="meta-item">{universe.works} Opere</span>
                    </div>
                </div>
            </div>

            <div className="tabs">
                {tabs.map(tab => (
                    <button
                        key={tab.id}
                        className={`tab ${activeTab === tab.id ? 'active' : ''}`}
                        onClick={() => setActiveTab(tab.id)}
                    >
                        {tab.label}
                        <span className="tab-count">{tab.count}</span>
                    </button>
                ))}
            </div>

            <div className="tab-content">
                {activeTab === 'characters' && (
                    <CharactersList universeUri={universe.uri} />
                )}
                {activeTab === 'locations' && (
                    <LocationsList universeUri={universe.uri} />
                )}
                {activeTab === 'works' && (
                    <WorksList universeUri={universe.uri} />
                )}
            </div>
        </div>
    );
}