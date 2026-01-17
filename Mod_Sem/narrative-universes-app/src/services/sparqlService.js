const GRAPHDB_ENDPOINT = 'http://localhost:3001/sparql';

export async function executeQuery(query) {
    const response = await fetch(GRAPHDB_ENDPOINT, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/sparql-query',
            'Accept': 'application/sparql-results+json'
        },
        body: query
    });

    if (!response.ok) throw new Error('Query failed');
    return await response.json();
}

export async function getUniverses() {
    const query = `
    PREFIX ontology: <http://www.narrative-universes.org/ontology#>
    PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
    
    SELECT ?universe ?name 
           (COUNT(DISTINCT ?character) AS ?numCharacters) 
           (COUNT(DISTINCT ?location) AS ?numLocations)
           (COUNT(DISTINCT ?work) AS ?numWorks)
    WHERE {
      ?universe a ontology:NarrativeUniverse ;
                rdfs:label ?name .
      OPTIONAL { 
        ?character a ontology:Character ;
                   ontology:belongsToUniverse ?universe 
      }
      OPTIONAL { 
        ?location a ontology:Location ;
                  ontology:belongsToUniverse ?universe 
      }
      OPTIONAL {
        ?work a ontology:NarrativeWork ;
              ontology:belongsToUniverse ?universe
      }
    }
    GROUP BY ?universe ?name
    ORDER BY ?name
  `;

    return executeQuery(query);
}

// Query: Personaggi per universo
export async function getCharactersByUniverse(universeUri) {
    const query = `
    PREFIX ontology: <http://www.narrative-universes.org/ontology#>
    PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>
    PREFIX rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#>
    
    SELECT DISTINCT ?character ?name ?type ?description
    WHERE {
      ?character a ontology:Character ;
                 rdfs:label ?name ;
                 ontology:belongsToUniverse <${universeUri}> .
      
      ?character rdf:type ?type .
      FILTER(STRSTARTS(STR(?type), STR(ontology:)))
      
      OPTIONAL { ?character ontology:description ?description }
    }
    ORDER BY ?name
  `;

    return executeQuery(query);
}