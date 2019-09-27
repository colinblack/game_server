package com.sanguo.game.server.connectlogic.common.message.ProtoPush
{
	import laya.utils.Byte;
	public class PushBuildingsCPP
	{
		public static const PROTO:String = "ProtoPush.PushBuildingsCPP";
		public var package_root:*;
		public  var message:*;
		public var buildings:Vector.<BuildingCPP>;
		public var croplands:Vector.<CropLandCPP>;
		public var equipments:Vector.<ProduceEquipCPP>;
		public var animals:Vector.<AnimalCPP>;
		public var equipmentstar:Vector.<EquipmentStarCPP>;
		public var fruits:Vector.<FruitCPP>;
		public var orders:Vector.<OrderCPP>;
		public var truck:TruckCPP;
		public var shipping:ShippingCPP;
		public var shipboxes:Vector.<ShippingBoxCPP>;
		public var commons:CommonItemsCPP;
		public function PushBuildingsCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			buildings = new Vector.<BuildingCPP>();
			croplands = new Vector.<CropLandCPP>();
			equipments = new Vector.<ProduceEquipCPP>();
			animals = new Vector.<AnimalCPP>();
			equipmentstar = new Vector.<EquipmentStarCPP>();
			fruits = new Vector.<FruitCPP>();
			orders = new Vector.<OrderCPP>();
			truck = undefined;
			shipping = undefined;
			shipboxes = new Vector.<ShippingBoxCPP>();
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.buildings = [];
			for(var i:int = 0;i < this.buildings.length;i++)
			{
				serializeObj.buildings.push(this.buildings[i].serialize());
			}
			serializeObj.croplands = [];
			for(var i:int = 0;i < this.croplands.length;i++)
			{
				serializeObj.croplands.push(this.croplands[i].serialize());
			}
			serializeObj.equipments = [];
			for(var i:int = 0;i < this.equipments.length;i++)
			{
				serializeObj.equipments.push(this.equipments[i].serialize());
			}
			serializeObj.animals = [];
			for(var i:int = 0;i < this.animals.length;i++)
			{
				serializeObj.animals.push(this.animals[i].serialize());
			}
			serializeObj.equipmentstar = [];
			for(var i:int = 0;i < this.equipmentstar.length;i++)
			{
				serializeObj.equipmentstar.push(this.equipmentstar[i].serialize());
			}
			serializeObj.fruits = [];
			for(var i:int = 0;i < this.fruits.length;i++)
			{
				serializeObj.fruits.push(this.fruits[i].serialize());
			}
			serializeObj.orders = [];
			for(var i:int = 0;i < this.orders.length;i++)
			{
				serializeObj.orders.push(this.orders[i].serialize());
			}
			if(this.truck!= undefined)
			{
				serializeObj.truck = this.truck.serialize();
			}
			if(this.shipping!= undefined)
			{
				serializeObj.shipping = this.shipping.serialize();
			}
			serializeObj.shipboxes = [];
			for(var i:int = 0;i < this.shipboxes.length;i++)
			{
				serializeObj.shipboxes.push(this.shipboxes[i].serialize());
			}
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushBuildingsCPP
		{
			buildings = new Vector.<BuildingCPP>();
			croplands = new Vector.<CropLandCPP>();
			equipments = new Vector.<ProduceEquipCPP>();
			animals = new Vector.<AnimalCPP>();
			equipmentstar = new Vector.<EquipmentStarCPP>();
			fruits = new Vector.<FruitCPP>();
			orders = new Vector.<OrderCPP>();
			truck = undefined;
			shipping = undefined;
			shipboxes = new Vector.<ShippingBoxCPP>();
			commons = undefined;
			for(var i:int = 0;i < msgObj.buildings.length;i++)
			{
				this.buildings.push(new BuildingCPP(package_root).unserialize(msgObj.buildings[i]));
			}
			for(var i:int = 0;i < msgObj.croplands.length;i++)
			{
				this.croplands.push(new CropLandCPP(package_root).unserialize(msgObj.croplands[i]));
			}
			for(var i:int = 0;i < msgObj.equipments.length;i++)
			{
				this.equipments.push(new ProduceEquipCPP(package_root).unserialize(msgObj.equipments[i]));
			}
			for(var i:int = 0;i < msgObj.animals.length;i++)
			{
				this.animals.push(new AnimalCPP(package_root).unserialize(msgObj.animals[i]));
			}
			for(var i:int = 0;i < msgObj.equipmentstar.length;i++)
			{
				this.equipmentstar.push(new EquipmentStarCPP(package_root).unserialize(msgObj.equipmentstar[i]));
			}
			for(var i:int = 0;i < msgObj.fruits.length;i++)
			{
				this.fruits.push(new FruitCPP(package_root).unserialize(msgObj.fruits[i]));
			}
			for(var i:int = 0;i < msgObj.orders.length;i++)
			{
				this.orders.push(new OrderCPP(package_root).unserialize(msgObj.orders[i]));
			}
			if(msgObj.hasOwnProperty("truck"))
			{
				this.truck = new TruckCPP(package_root).unserialize(msgObj.truck);
			}
			if(msgObj.hasOwnProperty("shipping"))
			{
				this.shipping = new ShippingCPP(package_root).unserialize(msgObj.shipping);
			}
			for(var i:int = 0;i < msgObj.shipboxes.length;i++)
			{
				this.shipboxes.push(new ShippingBoxCPP(package_root).unserialize(msgObj.shipboxes[i]));
			}
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushBuildingsCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}