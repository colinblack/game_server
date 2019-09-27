package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class GetThumbsUpResp
	{
		public static const PROTO:String = "User.GetThumbsUpResp";
		public var package_root:*;
		public  var message:*;
		public var thumbsup:ThumbsUpCPP;
		public function GetThumbsUpResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			thumbsup = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.thumbsup = this.thumbsup.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetThumbsUpResp
		{
			thumbsup = undefined;
			this.thumbsup = new ThumbsUpCPP(package_root).unserialize(msgObj.thumbsup);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetThumbsUpResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}