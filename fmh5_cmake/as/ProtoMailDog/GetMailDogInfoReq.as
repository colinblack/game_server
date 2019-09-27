package com.sanguo.game.server.connectlogic.common.message.ProtoMailDog
{
	import laya.utils.Byte;
	public class GetMailDogInfoReq
	{
		public static const PROTO:String = "ProtoMailDog.GetMailDogInfoReq";
		public var package_root:*;
		public  var message:*;
		public function GetMailDogInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetMailDogInfoReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetMailDogInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}