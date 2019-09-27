package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class RankThumbsUpResp
	{
		public static const PROTO:String = "User.RankThumbsUpResp";
		public var package_root:*;
		public  var message:*;
		public var thumbsup:ThumbsUpCPP;
		public var commons:CommonItemsCPP;
		public function RankThumbsUpResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			thumbsup = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.thumbsup = this.thumbsup.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):RankThumbsUpResp
		{
			thumbsup = undefined;
			commons = undefined;
			this.thumbsup = new ThumbsUpCPP(package_root).unserialize(msgObj.thumbsup);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RankThumbsUpResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}