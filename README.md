# Simple Inventory Management System with C

[![Open in Visual Studio Code](https://open.vscode.dev/badges/open-in-vscode.svg)](https://open.vscode.dev/EugeneYo/Simple-Inventory-Management-System-With-C)

# Table of Contents

- [Install Instructions](#install-instructions)
    - [For Windows](#for-windows)
- [Preview](#preview)
  - [Main Menu](#main-menu)
  - [Options Available](#options-available)
      - [1. View Existing Products](#1-view-existing-products)
      - [2. Add New Product](#2-add-new-product)
      - [3. Update Existing Products](#3-update-existing-products)
      - [4. Delete Existing Product](#4-delete-existing-product)
      - [5. Search Existing Product](#5-search-existing-product)
- [Mock Data](#mock-data)
- [About](#about)

# Install Instructions

- Either using `git clone` or

```
git clone https://github.com/EugeneYo/Simple-Inventory-Management-System-With-C.git
```

- Direct download the project as a zip file then extract it.

![Download](https://user-images.githubusercontent.com/31185780/124531447-1ca8d800-de41-11eb-9638-34d49356ca3f.jpg)

### For Windows

- After the project is downloaded or cloned, go into the project root directory
- run the following command

```
.\build.bat
```

<hr>

# Preview

## Main Menu

![Main Menu](https://user-images.githubusercontent.com/31185780/127428019-4577509b-8e8d-4155-91ae-a07bcabbe652.png)

## Options Available

#### 1. View Existing Products

![View Product](https://user-images.githubusercontent.com/31185780/127428452-ef86c72a-f529-4ea4-b725-6b43edc21743.png)

#### 2. Add New Product

![Add Product](https://user-images.githubusercontent.com/31185780/127428461-92165fa4-3998-438b-9ab2-59a70563320c.png)
![Add Product](https://user-images.githubusercontent.com/31185780/127428466-4ef9641e-c2cd-4253-891d-6f9f479d724d.png)

#### 3. Update Existing Products

![Update Existing Products](https://user-images.githubusercontent.com/31185780/127428473-a20a2145-09fc-4d77-850d-6483dcec45f8.png)
![Update Existing Products](https://user-images.githubusercontent.com/31185780/127428479-648ab863-5bbe-4061-aab3-cd7cfd9b9869.png)
![Update Existing Products](https://user-images.githubusercontent.com/31185780/127428485-e9ed2f16-a620-4f43-acd9-e3f22f85013c.png)

#### 4. Delete Existing Product

![Delete Existing Product](https://user-images.githubusercontent.com/31185780/127428488-bfafade8-0bb1-4e17-a609-326361902b75.png)
![Delete Existing Product](https://user-images.githubusercontent.com/31185780/127428498-0eab16ad-9602-42dd-a855-107734a40b81.png)

#### 5. Search Existing Product

![Search Existing Product](https://user-images.githubusercontent.com/31185780/127428506-33d27215-bb12-4cd0-aa29-aedccfd67e8e.png)
![Search Existing Product](https://user-images.githubusercontent.com/31185780/127428510-0da8e93a-1fff-4746-b4fe-3b01c51516ae.png)

<hr>

# Mock Data

- Data used to shown in the preview are generated from `mackaroo`
- Enter the following command into console to generate mock data or

```
curl "https://api.mockaroo.com/api/5317dd60?count=1000&key=e8d8ec90" > "Inventory.csv"
```

- Click this to generate the data you want : [Schema for this system](https://www.mockaroo.com/schemas/328195)
- I suggest not to change the `Field Name` set, but change only the options limiting the `Field Name` available

<hr>

# About

- This was made with the purpose of learning C programming language

<!--

### For Linux

- After the project is downloaded or cloned,go into the project root directory
- run the following command

````
./build.sh
``` -->
