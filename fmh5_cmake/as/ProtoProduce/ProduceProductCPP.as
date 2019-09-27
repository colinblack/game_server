package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class ProduceProductCPP
	{
		public static const PROTO:String = "ProtoProduce.ProduceProductCPP";
		public var package_root:*;
		public  var message:*;
		public var cropland:CropLandCPP;
		public var equipment:ProduceEquipCPP;
		public var animal:AnimalCPP;
		public var fruit:FruitCPP;
		public function ProduceProductCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			cropland = undefined;
			equipment = undefined;
			animal = undefined;
			fruit = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.cropland!= undefined)
			{
				serializeObj.cropland = this.cropland.serialize();
			}
			if(this.equipment!= undefined)
			{
				serializeObj.equipment = this.equipment.serialize();
			}
			if(this.animal!= undefined)
			{
				serializeObj.animal = this.animal.serialize();
			}
			if(this.fruit!= undefined)
			{
				serializeObj.fruit = this.fruit.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProduceProductCPP
		{
			cropland = undefined;
			equipment = undefined;
			animal = undefined;
			fruit = undefined;
			if(msgObj.hasOwnProperty("cropland"))
			{
				this.cropland = new CropLandCPP(package_root).unserialize(msgObj.cropland);
			}
			if(msgObj.hasOwnProperty("equipment"))
			{
				this.equipment = new ProduceEquipCPP(package_root).unserialize(msgObj.equipment);
			}
			if(msgObj.hasOwnProperty("animal"))
			{
				this.animal = new AnimalCPP(package_root).unserialize(msgObj.animal);
			}
			if(msgObj.hasOwnProperty("fruit"))
			{
				this.fruit = new FruitCPP(package_root).unserialize(msgObj.fruit);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProduceProductCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}