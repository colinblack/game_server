package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class UnlockCards
	{
		public static const PROTO:String = "User.UnlockCards";
		public var package_root:*;
		public  var message:*;
		public var unlockInfo:Vector.<UnlockCardsCPP>;
		public function UnlockCards(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			unlockInfo = new Vector.<UnlockCardsCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.unlockInfo = [];
			for(var i:int = 0;i < this.unlockInfo.length;i++)
			{
				serializeObj.unlockInfo.push(this.unlockInfo[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):UnlockCards
		{
			unlockInfo = new Vector.<UnlockCardsCPP>();
			for(var i:int = 0;i < msgObj.unlockInfo.length;i++)
			{
				this.unlockInfo.push(new UnlockCardsCPP(package_root).unserialize(msgObj.unlockInfo[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UnlockCards
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}