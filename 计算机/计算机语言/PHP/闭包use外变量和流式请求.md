## use和&

使用use来引用外面的变量，&引用对象可以修改值

## 案例

```php
$prev_chunk = "";
curl_setopt($ch, CURLOPT_WRITEFUNCTION, function ($ch, $chunk) use (&$prev_chunk) {
	$current_chunk = $prev_chunk . $chunk;
	$data_array = explode("data: ", $current_chunk);
	$res_content = '';
	$prev_chunk = "";
            for ($data_idx = 1; $data_idx < count($data_array); $data_idx++) {
                $data = $data_array[$data_idx];
                if ($data == "[DONE]\n\n") {
                    break;
                }
                $json_data = json_encode(substr($data, 0, -2), true);
                str_replace("\"", "\\\"", $json_data);
                $obj_data = json_decode(json_decode($json_data));
                if (json_last_error() != JSON_ERROR_NONE) {
                    for (;$data_idx < count($data_array); $data_idx++){
                        $prev_chunk = $prev_chunk . "data: " . $data_array[$data_idx];
                    }
                    break;
                }
                $content='';
                if(isset($obj_data->choices[0]->delta->content)){
                    $content = $obj_data->choices[0]->delta->content;
                }
                $res_content .= $content;
            }
            if($res_content == null || $res_content == ""){
                return strlen($chunk);
            }
            echo $res_content;
            $GLOBALS['generated_text'] .= $res_content;
            // $i = 1;
            // if (count($data_array) > 2)
            //     $i = 2;
            // if ($data_array[$i] == "[DONE]\n\n") {
            //     //ob_end_flush();
            //     return strlen($chunk);
            // }
            // $json_data = json_encode(substr($data_array[$i], 0, -2), true);
            // str_replace("\"", "\\\"", $json_data);
            // $obj_data = json_decode(json_decode($json_data));
            // $content = $obj_data->choices[0]->delta->content;
            // if ($content == null || $content == "") {
            //     return strlen($chunk);
            // }
            // echo $content;
            // $GLOBALS['generated_text'] .= $content;
            flush();
            ob_flush();
            return strlen($chunk);
});
        
// Make the API request
$response = curl_exec($ch);
```