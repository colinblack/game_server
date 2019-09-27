package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class EquipmentStarCPP
	{
		public static const PROTO:String = "ProtoNPCUser.EquipmentStarCPP";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var star:int;
		public var usedtime:int;
		public function EquipmentStarCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			star = undefined;
			usedtime = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.star = this.star;
			serializeObj.usedtime = this.usedtime;
			return serializeObj;
		}
		public function unserialize(msgObj:*):EquipmentStarCPP
		{
			id = undefined;
			star = undefined;
			usedtime = undefined;
			this.id = msgObj.id;
			this.star = msgObj.star;
			this.usedtime = msgObj.usedtime;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):EquipmentStarCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}