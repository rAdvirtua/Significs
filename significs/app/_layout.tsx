import { Stack } from 'expo-router';

export default function Layout() {
  return (
    <Stack screenOptions={{ headerShown: false }}>
      <Stack.Screen name="index" options={{ title: "Get Started" }} />
      <Stack.Screen name="connection" options={{ title: "Connection" }} />
    </Stack>
  );
}
