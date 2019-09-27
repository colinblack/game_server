package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class FetchDonationReq
	{
		public static const PROTO:String = "ProtoAlliance.FetchDonationReq";
		public var package_root:*;
		public  var message:*;
		public function FetchDonationReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):FetchDonationReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FetchDonationReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}