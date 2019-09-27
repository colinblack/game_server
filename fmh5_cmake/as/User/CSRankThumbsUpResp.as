package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class CSRankThumbsUpResp
	{
		public static const PROTO:String = "User.CSRankThumbsUpResp";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var index1:int;
		public var index2:int;
		public function CSRankThumbsUpResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			index1 = undefined;
			index2 = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.index1 = this.index1;
			serializeObj.index2 = this.index2;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSRankThumbsUpResp
		{
			myuid = undefined;
			index1 = undefined;
			index2 = undefined;
			this.myuid = msgObj.myuid;
			this.index1 = msgObj.index1;
			this.index2 = msgObj.index2;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSRankThumbsUpResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}