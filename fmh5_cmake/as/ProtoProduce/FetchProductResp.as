package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class FetchProductResp
	{
		public static const PROTO:String = "ProtoProduce.FetchProductResp";
		public var package_root:*;
		public  var message:*;
		public var equipment:ProduceEquipCPP;
		public var commons:CommonItemsCPP;
		public var isfull:Boolean;
		public function FetchProductResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			equipment = undefined;
			commons = undefined;
			isfull = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.equipment = this.equipment.serialize();
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			serializeObj.isfull = this.isfull;
			return serializeObj;
		}
		public function unserialize(msgObj:*):FetchProductResp
		{
			equipment = undefined;
			commons = undefined;
			isfull = undefined;
			this.equipment = new ProduceEquipCPP(package_root).unserialize(msgObj.equipment);
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			this.isfull = msgObj.isfull;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FetchProductResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}