package com.sanguo.game.server.connectlogic.common.message.ProtoPet
{
	import laya.utils.Byte;
	public class TeasePetReq
	{
		public static const PROTO:String = "ProtoPet.TeasePetReq";
		public var package_root:*;
		public  var message:*;
		public var petid:int;
		public function TeasePetReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			petid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.petid = this.petid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):TeasePetReq
		{
			petid = undefined;
			this.petid = msgObj.petid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):TeasePetReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}