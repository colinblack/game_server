package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class GetWorldChannelHelpCntResp
	{
		public static const PROTO:String = "User.GetWorldChannelHelpCntResp";
		public var package_root:*;
		public  var message:*;
		public var remainCnt:int;
		public function GetWorldChannelHelpCntResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			remainCnt = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.remainCnt = this.remainCnt;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetWorldChannelHelpCntResp
		{
			remainCnt = undefined;
			this.remainCnt = msgObj.remainCnt;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetWorldChannelHelpCntResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}