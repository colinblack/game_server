package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class ConcernResp
	{
		public static const PROTO:String = "ProtoFriend.ConcernResp";
		public var package_root:*;
		public  var message:*;
		public var concern:ConcernFolkCPP;
		public function ConcernResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			concern = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.concern = this.concern.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ConcernResp
		{
			concern = undefined;
			this.concern = new ConcernFolkCPP(package_root).unserialize(msgObj.concern);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ConcernResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}