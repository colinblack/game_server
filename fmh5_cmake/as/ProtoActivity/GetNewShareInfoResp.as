package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class GetNewShareInfoResp
	{
		public static const PROTO:String = "ProtoActivity.GetNewShareInfoResp";
		public var package_root:*;
		public  var message:*;
		public var friend:Vector.<ShareFriendCPP>;
		public var newShare:NewShareCPP;
		public var rewardFlag:Vector.<int>;
		public function GetNewShareInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			friend = new Vector.<ShareFriendCPP>();
			newShare = undefined;
			rewardFlag = new Vector.<int>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.friend = [];
			for(var i:int = 0;i < this.friend.length;i++)
			{
				serializeObj.friend.push(this.friend[i].serialize());
			}
			serializeObj.newShare = this.newShare.serialize();
			serializeObj.rewardFlag = [];
			for(var i:int = 0;i < this.rewardFlag.length;i++)
			{
				serializeObj.rewardFlag.push(this.rewardFlag[i]);
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetNewShareInfoResp
		{
			friend = new Vector.<ShareFriendCPP>();
			newShare = undefined;
			rewardFlag = new Vector.<int>();
			for(var i:int = 0;i < msgObj.friend.length;i++)
			{
				this.friend.push(new ShareFriendCPP(package_root).unserialize(msgObj.friend[i]));
			}
			this.newShare = new NewShareCPP(package_root).unserialize(msgObj.newShare);
			for(var i:int = 0;i < msgObj.rewardFlag.length;i++)
			{
				this.rewardFlag.push(msgObj.rewardFlag[i]);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetNewShareInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}