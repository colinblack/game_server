package com.sanguo.game.server.connectlogic.common.message.ProtoVIP
{
	import laya.utils.Byte;
	public class VIPAddProductQueueResp
	{
		public static const PROTO:String = "ProtoVIP.VIPAddProductQueueResp";
		public var package_root:*;
		public  var message:*;
		public var equip:ProduceEquipCPP;
		public function VIPAddProductQueueResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			equip = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.equip = this.equip.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):VIPAddProductQueueResp
		{
			equip = undefined;
			this.equip = new ProduceEquipCPP(package_root).unserialize(msgObj.equip);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):VIPAddProductQueueResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}