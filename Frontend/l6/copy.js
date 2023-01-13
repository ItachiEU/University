function cloneDeep(obj) {
  return JSON.parse(JSON.stringify(obj));
}

const user = {
  name: "Alice",
  surname: "Young",
  contact: {
    phone: '111-111-111',
    address: {
      city: "London",
    }
  }
};

const userCp = cloneDeep(user);

user.name = "John";
user.surname = "White";
user.contact.phone = '222-222-222';
user.contact.address.city = 'New York'

console.log(user);
/*
{ name: 'John',
  surname: 'White',
  contact: { 
    phone: '222-222-222', 
    address: { 
      city: 'New York' 
    } 
  } 
}
*/
console.log(userCp);
/*
{ 
  name: 'Alice',
  surname: 'Young',
  contact: { 
    phone: '111-111-111', 
    address: { 
      city: 'London' 
    } 
  } 
} 
*/