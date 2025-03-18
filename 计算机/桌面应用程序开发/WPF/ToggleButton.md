# ToggleButton

ToggleButton控件提供了一种在开/关状态之间切换的机制。

xaml:
```xml
	<Grid>
        <Grid.RowDefinitions>
            <RowDefinition Height="auto" />
            <RowDefinition />
        </Grid.RowDefinitions>
        <StackPanel Orientation="Horizontal" HorizontalAlignment="Center" Margin="20">
            <ToggleButton Content="Open Project" x:Name="openProjectButton" FontSize="32"
                          Click="OnToggleButton_Click"/>
            <ToggleButton Content="Create Porject" x:Name="createProjectButton" FontSize="32" Margin="30,0,0,0"
                          Click="OnToggleButton_Click"/>
        </StackPanel>
        <StackPanel Orientation="Horizontal" Grid.Row="1" x:Name="browserContent">
            <Border Width="800" Background="LightBlue">
                <TextBlock FontSize="72" Text="Open Project"/>
            </Border>
            <Border Width="800" Background="LightGreen">
                <TextBlock FontSize="72" Text="Create Project"/>
            </Border>
        </StackPanel>
    </Grid>
```

```Csharp
	private void OnToggleButton_Click(object sender, RoutedEventArgs e)
        {
            if(sender == openProjectButton)
            {
                if(createProjectButton.IsChecked == true)
                {
                    createProjectButton.IsChecked = false;
                    browserContent.Margin = new Thickness(0);
                }
                openProjectButton.IsChecked = true;
            }
            else
            {
                if (openProjectButton.IsChecked == true)
                {
                    openProjectButton.IsChecked = false;
                    browserContent.Margin = new Thickness(-800, 0, 0, 0);
                }
                createProjectButton.IsChecked = true;
            }
        }
```