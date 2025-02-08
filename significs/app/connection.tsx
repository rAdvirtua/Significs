import { View, Text, StyleSheet } from 'react-native';

export default function Connection() {
  return (
    <View style={styles.container}>
      <Text style={styles.title}>CONNECTION</Text>
      <Text style={styles.subtitle}>Connect your flex sensor glove using Bluetooth</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#5577F9',
    justifyContent: 'center',
    alignItems: 'center',
  },
  title: {
    fontSize: 28,
    fontWeight: 'bold',
    fontStyle: 'italic',
    color: 'rgba(255, 255, 255, 0.92)', // White with 92% opacity
  },
  subtitle: {
    fontSize: 18,
    color: 'rgba(255, 255, 255, 0.92)', // White with 92% opacity
    marginTop: 10,
    textAlign: 'center',
  },
});
