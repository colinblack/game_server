package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class RankThumbsUpReq
	{
		public static const PROTO:String = "User.RankThumbsUpReq";
		public var package_root:*;
		public  var message:*;
		public var othuid:int;
		public var index1:int;
		public var index2:int;
		public function RankThumbsUpReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			othuid = undefined;
			index1 = undefined;
			index2 = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.othuid = this.othuid;
			serializeObj.index1 = this.index1;
			serializeObj.index2 = this.index2;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RankThumbsUpReq
		{
			othuid = undefined;
			index1 = undefined;
			index2 = undefined;
			this.othuid = msgObj.othuid;
			this.index1 = msgObj.index1;
			this.index2 = msgObj.index2;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RankThumbsUpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}