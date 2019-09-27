package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class CSConcernResp
	{
		public static const PROTO:String = "ProtoFriend.CSConcernResp";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var folkResp:ConcernResp;
		public function CSConcernResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			folkResp = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.folkResp = this.folkResp.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSConcernResp
		{
			myuid = undefined;
			folkResp = undefined;
			this.myuid = msgObj.myuid;
			this.folkResp = new ConcernResp(package_root).unserialize(msgObj.folkResp);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSConcernResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}