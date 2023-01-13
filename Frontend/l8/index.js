const pokeList = document.querySelector(".poke-list");
const currentPokemon = document.querySelector(".pokemon-chosen");
let pokemonList = [];

const fetchPokemon = () => {
   fetch('https://pokeapi.co/api/v2/pokemon?limit=151')
      .then(response => response.json())
      .then(allpokemon => {
         savePokemon(allpokemon.results);
      })
      .then(_ =>
         renderPokemonList()
      )
      .catch(e => {
         console.log(e)
         pokeList.innerHTML = "<span>Couldn't fetch pokemon list.</span>"
      }
      )
}

const capitalize = (str) => {currentPokemon
   return str.length === 0 ? '' : str[0].toUpperCase() + str.slice(1);
}

const renderPokemonList = () => {
   let liTag = "";
   if (pokemonList) {
      pokemonList.forEach((pokemon, id) => {
         liTag += `<li class="pokemon">
                     <label for="${id}">
                       <p>${capitalize(pokemon.name)}</p>
                     </label>
                     <div>
                        <button id='button_${id}'">
                           Show Pokemon
                        </button>
                     <div>
                  </li>`;
      });
   }
   pokeList.innerHTML = liTag || `<span>Couldn't load any pokemons</span>`;
   pokemonList.forEach((pokemon, id) => {
      let buttonElement = document.getElementById(`button_${id}`);
      currentPokemon.innerHTML = "";
      buttonElement.addEventListener("click", e => {
         fetch(pokemon.url)
            .then(response => response.json())
            .then(pokeData => {
                  console.log(pokeData);
                  let liElements = pokeData.types.map((type, id) => `<li>${type.type.name}</li>`).join('');
                  currentPokemon.innerHTML = `
                  <p>${pokeData.name}</p>
                  <img src='${pokeData.sprites.front_default}'></img>
                  <ul>
                     ${liElements}
                  </ul>
               `
                  return pokeData;
               }
            )  
            .then(pokeData =>
               fetchPokemonDescription(pokeData.species.url)
            )
            .catch(e => {
               console.log(e);
               currentPokemon.innerHTML = "<p>Couldn't get pokemon's details</p>";
         })
      });
   });
}

const fetchPokemonDescription = (speciecies_url) => {
   console.log(speciecies_url);
   fetch(speciecies_url)
      .then(response => response.json())
      .then(pokeData => {
         return pokeData.flavor_text_entries[0].flavor_text;
      })
      .then(description => {
         currentPokemon.innerHTML =
            currentPokemon.innerHTML + `<span>${description}</span>`;
      })
}

const savePokemon = (pokemons) => {
   pokemonList = pokemons;
   console.log(pokemonList);
}

fetchPokemon();

