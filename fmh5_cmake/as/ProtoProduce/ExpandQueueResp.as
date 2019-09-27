package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class ExpandQueueResp
	{
		public static const PROTO:String = "ProtoProduce.ExpandQueueResp";
		public var package_root:*;
		public  var message:*;
		public var equipment:ProduceEquipCPP;
		public var commons:CommonItemsCPP;
		public function ExpandQueueResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			equipment = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.equipment = this.equipment.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ExpandQueueResp
		{
			equipment = undefined;
			commons = undefined;
			this.equipment = new ProduceEquipCPP(package_root).unserialize(msgObj.equipment);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ExpandQueueResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}