// Define the list of cards that can be used in the flow editor
const cards = [
  { id: 1, name: "Trigger", type: "Trigger", mode: "Input" },
  {
    id: 2,
    name: "ValueSetter",
    type: "ValueSetter",
    mode: "InputOutput",
    parameters: [
      { name: "Value", type: "number", value: 0 },
      { name: "Expression", type: "string", value: "" },
    ],
  },
  {
    id: 3,
    name: "LinkIn",
    type: "LinkIn",
    mode: "Input",
  },
  {
    id: 4,
    name: "LinkOut",
    type: "LinkOut",
    mode: "Output",
    parameters: [{ name: "Target", type: "string", value: "" }],
  },
  {
    id: 5,
    name: "Logger",
    type: "Logger",
    mode: "Output",
    parameters: [{ name: "Prefix", type: "string", value: "" }],
  },
  {
    id: 6,
    name: "Filter",
    type: "Filter",
    mode: "InputOutput",
    parameters: [
      { name: "Condition", type: "string", value: "" },
      { name: "Variable", type: "string", value: "" },
    ],
  },
  {
    id: 7,
    name: "Math",
    type: "Math",
    mode: "InputOutput",
    parameters: [
      { name: "Operation", type: "string", value: "" },
      { name: "Variable", type: "string", value: "" },
    ],
  },
  {
    id: 8,
    name: "Counter",
    type: "Counter",
    mode: "InputOutput",
    parameters: [
      { name: "Variable", type: "string", value: "" },
      { name: "Step", type: "number", value: 1 },
    ],
  },
  {
    id: 9,
    name: "Delay",
    type: "Delay",
    mode: "InputOutput",
    parameters: [
      { name: "Delay", type: "number", value: 0 },
      { name: "Variable", type: "string", value: "" },
    ],
  },
  {
    id: 10,
    name: "Script",
    type: "Script",
    mode: "InputOutput",
    parameters: [{ name: "Expression", type: "string", value: "" }],
  },
  {
    id: 11,
    name: "MqttIn",
    type: "MqttIn",
    mode: "Input",
    parameters: [
      { name: "Topic", type: "string", value: "" },
      { name: "Variable", type: "string", value: "" },
      { name: "Host", type: "string", value: "" },
      { name: "ClientId", type: "string", value: "" },
      { name: "Username", type: "string", value: "" },
      { name: "Password", type: "string", value: "" },
      { name: "Port", type: "number", value: 1883 },
    ],
  },
  {
    id: 12,
    name: "MqttOut",
    type: "MqttOut",
    mode: "Output",
    parameters: [
      { name: "Topic", type: "string", value: "" },
      { name: "Variable", type: "string", value: "" },
      { name: "Host", type: "string", value: "" },
      { name: "ClientId", type: "string", value: "" },
      { name: "Username", type: "string", value: "" },
      { name: "Password", type: "string", value: "" },
      { name: "Port", type: "number", value: 1883 },
    ],
  },
];


const rightSidebarStyle = {
  display: "flex",
  flexDirection: "column",
  gap: "10px",
  padding: "10px",
  border: "1px solid #ccc",
  width: "200px",
  height: "100vh",
  position: "fixed",
  right: 0,
  top: 0,
  backgroundColor: "#f4f4f4",
};

const leftSidebarStyle = {
  display: "grid",
  gridTemplateColumns: "1fr 1fr",
  gap: "10px",
  padding: "10px",
  border: "1px solid #ccc",
  width: "200px",
  position: "fixed",
  left: 0,
  top: 0,
  backgroundColor: "#f4f4f4",
  overflowY: "auto",
  maxHeight: "100vh",
};

const cardStyle = {
  border: "1px solid #ccc",
  padding: "10px",
  borderRadius: "5px",
  backgroundColor: "#fff",
  height: "50px",
};
