const pokemonListElement = document.getElementById("pokemon-list");
const pokemonInfoSectionElement = document.getElementById("pokemon-info");

const POKEMON_API_BASE_URL = "https://pokeapi.co/api/v2";

function fetchAllPokemons() {
  return fetch(`${POKEMON_API_BASE_URL}/pokemon?offset=0&limit=151`);
}

function fetchPokemon(name) {
  return fetch(`${POKEMON_API_BASE_URL}/pokemon/${name}`);
}

function fetchPokemonSpecies(name) {
  return fetch(`${POKEMON_API_BASE_URL}/pokemon-species/${name}`);
}

function capitalize(string) {
  return string[0].toUpperCase() + string.slice(1);
}

function createErrorNotification(message) {
  const headerElement = document.createElement("h2");
  headerElement.textContent = "Error";

  const textElement = document.createElement("span");
  textElement.classList.add("notification", "notification--danger");
  textElement.textContent = message;

  const containerElement = document.createElement("div");
  containerElement.classList.add("container", "container--error");
  containerElement.appendChild(headerElement);
  containerElement.appendChild(textElement);

  return containerElement;
}

function createPokemonListItemElement(name) {
  const nameElement = document.createElement("span");
  nameElement.textContent = capitalize(name);

  const listItemElement = document.createElement("li");
  listItemElement.classList.add(
    "pokemon_list__item",
    "button",
    "button--select"
  );
  listItemElement.setAttribute("id", name);
  listItemElement.addEventListener("click", () => loadPokemonInfo(name));
  listItemElement.appendChild(nameElement);

  return listItemElement;
}

async function loadPokemonList() {
  const response = await fetchAllPokemons();
  const data = await response.json();
  const pokemonList = data.results;
  pokemonList.forEach(({ name }) => {
    const pokemonListItemElement = createPokemonListItemElement(name);
    pokemonListElement.appendChild(pokemonListItemElement);
  });
}

function createPokemonInfoElement({ name, sprites, types }, species) {
  const nameElement = document.createElement("h2");
  nameElement.textContent = capitalize(name);

  const imageElement = document.createElement("img");
  imageElement.src = sprites.front_default;

  const typesContainerElement = document.createElement("div");
  typesContainerElement.classList.add("pokemon_type__container");

  types.forEach(({ type }) => {
    const typeBadgeElement = document.createElement("div");
    typeBadgeElement.classList.add("pokemon_type__badge");

    const typeTextElement = document.createElement("span");
    typeTextElement.textContent = type.name;

    typeBadgeElement.appendChild(typeTextElement);
    typesContainerElement.appendChild(typeBadgeElement);
  });

  const descriptionElement = document.createElement("span");
  descriptionElement.textContent = species.flavor_text_entries[0].flavor_text;

  const containerElement = document.createElement("div");
  containerElement.classList.add("pokemon_info__container");
  containerElement.appendChild(nameElement);
  containerElement.appendChild(imageElement);
  containerElement.appendChild(typesContainerElement);
  containerElement.appendChild(descriptionElement);

  return containerElement;
}

function showPokemonLoadErrorNotification(name) {
  const errorNotificationElement = createErrorNotification(
    `Failed to load ${capitalize(name)}`
  );

  pokemonInfoSectionElement.replaceChildren(errorNotificationElement);
}

async function loadPokemonInfo(name) {
  try {
    const pokemonResponse = await fetchPokemon(name);
    const speciesResponse = await fetchPokemonSpecies(name);
    if (!pokemonResponse.ok || !speciesResponse.ok)
      return showPokemonLoadErrorNotification(name);

    const pokemon = await pokemonResponse.json();
    const species = await speciesResponse.json();
    const pokemonInfoElement = createPokemonInfoElement(pokemon, species);
    pokemonInfoSectionElement.replaceChildren(pokemonInfoElement);
  } catch (error) {
    showPokemonLoadErrorNotification(name);
  }
}

loadPokemonList();
