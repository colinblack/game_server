package com.sanguo.game.server.connectlogic.common.message.ProtoPet
{
	import laya.utils.Byte;
	public class FeedPetReq
	{
		public static const PROTO:String = "ProtoPet.FeedPetReq";
		public var package_root:*;
		public  var message:*;
		public var petid:int;
		public function FeedPetReq(root:*)
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
		public function unserialize(msgObj:*):FeedPetReq
		{
			petid = undefined;
			this.petid = msgObj.petid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FeedPetReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}