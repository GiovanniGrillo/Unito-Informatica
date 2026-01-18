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
    
    SELECT ?universe ?name (SAMPLE(?desc) AS ?description)
           (COUNT(DISTINCT ?character) AS ?numCharacters) 
           (COUNT(DISTINCT ?location) AS ?numLocations)
           (COUNT(DISTINCT ?work) AS ?numWorks)
    WHERE {
      ?universe a ontology:NarrativeUniverse ;
                rdfs:label ?name .
      OPTIONAL { ?universe ontology:description ?desc }
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

export async function getWorksByUniverse(universeUri) {
    const query = `
    PREFIX ontology: <http://www.narrative-universes.org/ontology#>
    PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

    SELECT DISTINCT ?work ?title ?type ?year ?runtime ?pages
    WHERE {
        ?work a ontology:NarrativeWork ;
              ontology:belongsToUniverse <${universeUri}> ;
              rdfs:label ?title .

        BIND(
            IF(EXISTS { ?work a ontology:Book }, "Book",
               IF(EXISTS { ?work a ontology:Movie }, "Movie",
                  IF(EXISTS { ?work a ontology:TelevisionSeries }, "TVSeries",
                     "NarrativeWork"
                  )
               )
            ) AS ?type
        )

        OPTIONAL { ?work ontology:publicationYear ?year }
        OPTIONAL { ?work ontology:runtime ?runtime }
        OPTIONAL { ?work ontology:numberOfPages ?pages }
    }
    ORDER BY ?title
    `;

    return executeQuery(query);
}

export async function getLocationsByUniverse(universeUri) {
    const query = `
    PREFIX ontology: <http://www.narrative-universes.org/ontology#>
    PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

    SELECT DISTINCT ?location ?name ?type ?function ?danger
    WHERE {
        ?location a ontology:Location ;
                  ontology:belongsToUniverse <${universeUri}> ;
                  rdfs:label ?name .

        OPTIONAL { 
            ?location rdf:type ?typeRaw .
            FILTER(STRSTARTS(STR(?typeRaw), STR(ontology:)))
            BIND(STRAFTER(STR(?typeRaw), "#") AS ?type)
        }

        OPTIONAL { ?location ontology:hasNarrativeFunction ?function }
        OPTIONAL { ?location ontology:dangerLevel ?danger }
    }
    ORDER BY ?name
    `;

    return executeQuery(query);
}

export async function getEntityDetails(uri) {
    const baseQuery = `
    PREFIX ontology: <http://www.narrative-universes.org/ontology#>
    PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

    SELECT ?type ?label ?description
    WHERE {
        <${uri}> rdfs:label ?label .
        OPTIONAL { <${uri}> ontology:description ?description }
        <${uri}> rdf:type ?type .
        FILTER(STRSTARTS(STR(?type), STR(ontology:)))
    }
    `;

    const base = await executeQuery(baseQuery);
    const info = base.results.bindings[0];

    const type = info.type.value.split('#').pop();

    let relations = {};

    if (type === 'Character') {
        relations = await getCharacterRelations(uri);
    } else if (type === 'Location') {
        relations = await getLocationRelations(uri);
    } else if (type === 'NarrativeWork') {
        relations = await getWorkRelations(uri);
    } else if (type === 'Object') {
        relations = await getObjectRelations(uri);
    }

    return {
        uri,
        type,
        label: info.label.value,
        description: info.description?.value || '',
        ...relations
    };
}

export async function getCharacterRelations(uri) {
    const query = `
    PREFIX ontology: <http://www.narrative-universes.org/ontology#>
    PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

    SELECT ?ally ?enemy ?mentor ?student ?object ?ability ?work ?org
    WHERE {
        OPTIONAL { <${uri}> ontology:alliedWith ?ally }
        OPTIONAL { <${uri}> ontology:enemyOf ?enemy }
        OPTIONAL { <${uri}> ontology:mentors ?student }
        OPTIONAL { ?mentor ontology:mentors <${uri}> }
        OPTIONAL { <${uri}> ontology:possesses ?object }
        OPTIONAL { <${uri}> ontology:hasAbility ?ability }
        OPTIONAL { <${uri}> ontology:appearsIn ?work }
        OPTIONAL { <${uri}> ontology:memberOf ?org }
    }
    `;

    const data = await executeQuery(query);

    const extract = field =>
        [...new Set(data.results.bindings
            .filter(b => b[field])
            .map(b => b[field].value))];

    return {
        allies: extract('ally'),
        enemies: extract('enemy'),
        mentors: extract('mentor'),
        students: extract('student'),
        objects: extract('object'),
        abilities: extract('ability'),
        works: extract('work'),
        organizations: extract('org')
    };
}

export async function getLocationRelations(uri) {
    const query = `
    PREFIX ontology: <http://www.narrative-universes.org/ontology#>
    PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

    SELECT ?work ?org ?parent ?child ?function ?danger
    WHERE {
        OPTIONAL { ?work ontology:setIn <${uri}> }
        OPTIONAL { <${uri}> ontology:ospita ?org }
        OPTIONAL { <${uri}> ontology:partOf ?parent }
        OPTIONAL { ?child ontology:partOf <${uri}> }
        OPTIONAL { <${uri}> ontology:hasNarrativeFunction ?function }
        OPTIONAL { <${uri}> ontology:dangerLevel ?danger }
    }
    `;

    const data = await executeQuery(query);

    const extract = field =>
        [...new Set(data.results.bindings
            .filter(b => b[field])
            .map(b => b[field].value))];

    return {
        works: extract('work'),
        organizations: extract('org'),
        parentLocations: extract('parent'),
        childLocations: extract('child'),
        narrativeFunction: data.results.bindings[0]?.function?.value || null,
        dangerLevel: data.results.bindings[0]?.danger?.value || null
    };
}
export async function getObjectRelations() {
    return {};
}
export async function getWorkRelations(uri) {
    const query = `
    PREFIX ontology: <http://www.narrative-universes.org/ontology#>
    PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

    SELECT ?character ?main ?location ?prequel ?sequel ?adapt
    WHERE {
        OPTIONAL { <${uri}> ontology:features ?character }
        OPTIONAL { <${uri}> ontology:hasMainProtagonist ?main }
        OPTIONAL { <${uri}> ontology:setIn ?location }
        OPTIONAL { <${uri}> ontology:prequelOf ?sequel }
        OPTIONAL { ?prequel ontology:prequelOf <${uri}> }
        OPTIONAL { <${uri}> ontology:adaptationOf ?adapt }
    }
    `;

    const data = await executeQuery(query);

    const extract = field =>
        [...new Set(data.results.bindings
            .filter(b => b[field])
            .map(b => b[field].value))];

    return {
        characters: extract('character'),
        mainProtagonist: extract('main')[0] || null,
        locations: extract('location'),
        prequels: extract('prequel'),
        sequels: extract('sequel'),
        adaptations: extract('adapt')
    };
}


export async function getUniverseDetails(uri) {
    const query = `
    PREFIX ontology: <http://www.narrative-universes.org/ontology#>
    PREFIX rdfs: <http://www.w3.org/2000/01/rdf-schema#>

    SELECT ?name
           (COUNT(DISTINCT ?character) AS ?numCharacters)
           (COUNT(DISTINCT ?location) AS ?numLocations)
           (COUNT(DISTINCT ?work) AS ?numWorks)
    WHERE {
        <${uri}> a ontology:NarrativeUniverse ;
                 rdfs:label ?name .

        OPTIONAL { ?character a ontology:Character ; ontology:belongsToUniverse <${uri}> }
        OPTIONAL { ?location a ontology:Location ; ontology:belongsToUniverse <${uri}> }
        OPTIONAL { ?work a ontology:NarrativeWork ; ontology:belongsToUniverse <${uri}> }
    }
    GROUP BY ?name
    `;

    return executeQuery(query);
}
